/*
 * Copyright 2002 Andriy Palamarchuk
 *
 * Conformance test of the workstation functions.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "wine/test.h"
#include "winbase.h"
#include "winerror.h"
#include "nb30.h"
#include "lmcons.h"
#include "lmerr.h"
#include "lmwksta.h"
#include "lmapibuf.h"

static NET_API_STATUS (WINAPI *pNetApiBufferFree)(LPVOID)=NULL;
static NET_API_STATUS (WINAPI *pNetApiBufferSize)(LPVOID,LPDWORD)=NULL;
static NET_API_STATUS (WINAPI *pNetpGetComputerName)(LPWSTR*)=NULL;
static NET_API_STATUS (WINAPI *pNetWkstaUserGetInfo)(LPWSTR,DWORD,PBYTE*)=NULL;

WCHAR user_name[UNLEN + 1];
WCHAR computer_name[MAX_COMPUTERNAME_LENGTH + 1];

static int init_wksta_tests(void)
{
    DWORD dwSize;
    BOOL rc;

    user_name[0] = 0;
    dwSize = sizeof(user_name);
    rc=GetUserNameW(user_name, &dwSize);
    if (rc==FALSE && GetLastError()==ERROR_CALL_NOT_IMPLEMENTED)
        return 0;
    ok(rc, "User Name Retrieved");

    computer_name[0] = 0;
    dwSize = sizeof(computer_name);
    ok(GetComputerNameW(computer_name, &dwSize), "Computer Name Retrieved");
    return 1;
}

static void run_get_comp_name_tests(void)
{
    WCHAR empty[] = {0};
    LPWSTR ws = empty;
    if (!pNetpGetComputerName)
        return;

    ok(pNetpGetComputerName(&ws) == NERR_Success, "Computer name is retrieved");
    ok(!lstrcmpW(computer_name, ws), "This is really computer name");
    pNetApiBufferFree(ws);
}

static void run_wkstausergetinfo_tests(void)
{
    LPWKSTA_USER_INFO_0 ui0 = NULL;
    LPWKSTA_USER_INFO_1 ui1 = NULL;
    LPWKSTA_USER_INFO_1101 ui1101 = NULL;
    DWORD dwSize;

    if (!pNetWkstaUserGetInfo)
        return;

    /* Level 0 */
    ok(pNetWkstaUserGetInfo(NULL, 0, (LPBYTE *)&ui0) == NERR_Success,
       "NetWkstaUserGetInfo is successful");
    ok(!lstrcmpW(user_name, ui0->wkui0_username), "This is really user name");
    pNetApiBufferSize(ui0, &dwSize);
    ok(dwSize >= (sizeof(WKSTA_USER_INFO_0) +
                 lstrlenW(ui0->wkui0_username) * sizeof(WCHAR)),
       "Is allocated with NetApiBufferAllocate");

    /* Level 1 */
    ok(pNetWkstaUserGetInfo(NULL, 1, (LPBYTE *)&ui1) == NERR_Success,
       "NetWkstaUserGetInfo is successful");
    ok(lstrcmpW(ui1->wkui1_username, ui0->wkui0_username) == 0,
       "the same name as returned for level 0");
    pNetApiBufferSize(ui1, &dwSize);
    ok(dwSize >= (sizeof(WKSTA_USER_INFO_1) +
                  (lstrlenW(ui1->wkui1_username) +
                   lstrlenW(ui1->wkui1_logon_domain) +
                   lstrlenW(ui1->wkui1_oth_domains) +
                   lstrlenW(ui1->wkui1_logon_server)) * sizeof(WCHAR)),
       "Is allocated with NetApiBufferAllocate");

    /* Level 1101 */
    ok(pNetWkstaUserGetInfo(NULL, 1101, (LPBYTE *)&ui1101) == NERR_Success,
       "NetWkstaUserGetInfo is successful");
    ok(lstrcmpW(ui1101->wkui1101_oth_domains, ui1->wkui1_oth_domains) == 0,
       "the same oth_domains as returned for level 1");
    pNetApiBufferSize(ui1101, &dwSize);
    ok(dwSize >= (sizeof(WKSTA_USER_INFO_1101) +
                 lstrlenW(ui1101->wkui1101_oth_domains) * sizeof(WCHAR)),
       "Is allocated with NetApiBufferAllocate");

    pNetApiBufferFree(ui0);
    pNetApiBufferFree(ui1);
    pNetApiBufferFree(ui1101);

    /* errors handling */
    ok(pNetWkstaUserGetInfo(NULL, 10000, (LPBYTE *)&ui0) == ERROR_INVALID_LEVEL,
       "Invalid level");
}

START_TEST(wksta)
{
    HMODULE hnetapi32=LoadLibraryA("netapi32.dll");
    pNetApiBufferFree=(void*)GetProcAddress(hnetapi32,"NetApiBufferFree");
    pNetApiBufferSize=(void*)GetProcAddress(hnetapi32,"NetApiBufferSize");
    pNetpGetComputerName=(void*)GetProcAddress(hnetapi32,"NetpGetComputerName");
    pNetWkstaUserGetInfo=(void*)GetProcAddress(hnetapi32,"NetWkstaUserGetInfo");
    if (!pNetApiBufferSize)
        trace("It appears there is no netapi32 functionality on this platform\n");

    if (init_wksta_tests()) {
        run_get_comp_name_tests();
        run_wkstausergetinfo_tests();
    }
}
