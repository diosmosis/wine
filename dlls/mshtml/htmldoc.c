/*
 * Copyright 2005-2009 Jacek Caban for CodeWeavers
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
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include "config.h"

#include <stdarg.h>
#include <stdio.h>

#define COBJMACROS

#include "windef.h"
#include "winbase.h"
#include "winuser.h"
#include "wininet.h"
#include "ole2.h"
#include "perhist.h"
#include "mshtmdid.h"

#include "wine/debug.h"

#include "mshtml_private.h"
#include "htmlevent.h"
#include "pluginhost.h"

WINE_DEFAULT_DEBUG_CHANNEL(mshtml);

static inline HTMLDocument *impl_from_IHTMLDocument2(IHTMLDocument2 *iface)
{
    return CONTAINING_RECORD(iface, HTMLDocument, IHTMLDocument2_iface);
}

static HRESULT WINAPI HTMLDocument_QueryInterface(IHTMLDocument2 *iface, REFIID riid, void **ppv)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    return htmldoc_query_interface(This, riid, ppv);
}

static ULONG WINAPI HTMLDocument_AddRef(IHTMLDocument2 *iface)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    return htmldoc_addref(This);
}

static ULONG WINAPI HTMLDocument_Release(IHTMLDocument2 *iface)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    return htmldoc_release(This);
}

static HRESULT WINAPI HTMLDocument_GetTypeInfoCount(IHTMLDocument2 *iface, UINT *pctinfo)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    return IDispatchEx_GetTypeInfoCount(&This->IDispatchEx_iface, pctinfo);
}

static HRESULT WINAPI HTMLDocument_GetTypeInfo(IHTMLDocument2 *iface, UINT iTInfo,
                                                LCID lcid, ITypeInfo **ppTInfo)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    return IDispatchEx_GetTypeInfo(&This->IDispatchEx_iface, iTInfo, lcid, ppTInfo);
}

static HRESULT WINAPI HTMLDocument_GetIDsOfNames(IHTMLDocument2 *iface, REFIID riid,
                                                LPOLESTR *rgszNames, UINT cNames,
                                                LCID lcid, DISPID *rgDispId)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    return IDispatchEx_GetIDsOfNames(&This->IDispatchEx_iface, riid, rgszNames, cNames, lcid,
            rgDispId);
}

static HRESULT WINAPI HTMLDocument_Invoke(IHTMLDocument2 *iface, DISPID dispIdMember,
                            REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams,
                            VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    return IDispatchEx_Invoke(&This->IDispatchEx_iface, dispIdMember, riid, lcid, wFlags,
            pDispParams, pVarResult, pExcepInfo, puArgErr);
}

static HRESULT WINAPI HTMLDocument_get_Script(IHTMLDocument2 *iface, IDispatch **p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%p)\n", This, p);

    *p = (IDispatch*)&This->window->IHTMLWindow2_iface;
    IDispatch_AddRef(*p);
    return S_OK;
}

static HRESULT WINAPI HTMLDocument_get_all(IHTMLDocument2 *iface, IHTMLElementCollection **p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    nsIDOMElement *nselem = NULL;
    HTMLDOMNode *node;
    nsresult nsres;
    HRESULT hres;

    TRACE("(%p)->(%p)\n", This, p);

    if(!This->doc_node->nsdoc) {
        WARN("NULL nsdoc\n");
        return E_UNEXPECTED;
    }

    nsres = nsIDOMHTMLDocument_GetDocumentElement(This->doc_node->nsdoc, &nselem);
    if(NS_FAILED(nsres)) {
        ERR("GetDocumentElement failed: %08x\n", nsres);
        return E_FAIL;
    }

    if(!nselem) {
        *p = NULL;
        return S_OK;
    }

    hres = get_node(This->doc_node, (nsIDOMNode*)nselem, TRUE, &node);
    if(SUCCEEDED(hres))
        *p = create_all_collection(node, TRUE);
    nsIDOMElement_Release(nselem);
    return hres;
}

static HRESULT WINAPI HTMLDocument_get_body(IHTMLDocument2 *iface, IHTMLElement **p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    nsIDOMHTMLElement *nsbody = NULL;
    HTMLDOMNode *node;
    HRESULT hres;

    TRACE("(%p)->(%p)\n", This, p);

    if(This->doc_node->nsdoc) {
        nsresult nsres;

        nsres = nsIDOMHTMLDocument_GetBody(This->doc_node->nsdoc, &nsbody);
        if(NS_FAILED(nsres)) {
            TRACE("Could not get body: %08x\n", nsres);
            return E_UNEXPECTED;
        }
    }

    if(!nsbody) {
        *p = NULL;
        return S_OK;
    }

    hres = get_node(This->doc_node, (nsIDOMNode*)nsbody, TRUE, &node);
    nsIDOMHTMLElement_Release(nsbody);
    if(FAILED(hres))
        return hres;

    return IHTMLDOMNode_QueryInterface(&node->IHTMLDOMNode_iface, &IID_IHTMLElement, (void**)p);
}

static HRESULT WINAPI HTMLDocument_get_activeElement(IHTMLDocument2 *iface, IHTMLElement **p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_images(IHTMLDocument2 *iface, IHTMLElementCollection **p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    nsIDOMHTMLCollection *nscoll = NULL;
    nsresult nsres;

    TRACE("(%p)->(%p)\n", This, p);

    if(!p)
        return E_INVALIDARG;

    *p = NULL;

    if(!This->doc_node->nsdoc) {
        WARN("NULL nsdoc\n");
        return E_UNEXPECTED;
    }

    nsres = nsIDOMHTMLDocument_GetImages(This->doc_node->nsdoc, &nscoll);
    if(NS_FAILED(nsres)) {
        ERR("GetImages failed: %08x\n", nsres);
        return E_FAIL;
    }

    if(nscoll) {
        *p = create_collection_from_htmlcol(This->doc_node, (IUnknown*)&This->IHTMLDocument2_iface, nscoll);
        nsIDOMElement_Release(nscoll);
    }

    return S_OK;
}

static HRESULT WINAPI HTMLDocument_get_applets(IHTMLDocument2 *iface, IHTMLElementCollection **p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    nsIDOMHTMLCollection *nscoll = NULL;
    nsresult nsres;

    TRACE("(%p)->(%p)\n", This, p);

    if(!p)
        return E_INVALIDARG;

    *p = NULL;

    if(!This->doc_node->nsdoc) {
        WARN("NULL nsdoc\n");
        return E_UNEXPECTED;
    }

    nsres = nsIDOMHTMLDocument_GetApplets(This->doc_node->nsdoc, &nscoll);
    if(NS_FAILED(nsres)) {
        ERR("GetApplets failed: %08x\n", nsres);
        return E_FAIL;
    }

    if(nscoll) {
        *p = create_collection_from_htmlcol(This->doc_node, (IUnknown*)&This->IHTMLDocument2_iface, nscoll);
        nsIDOMElement_Release(nscoll);
    }

    return S_OK;
}

static HRESULT WINAPI HTMLDocument_get_links(IHTMLDocument2 *iface, IHTMLElementCollection **p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    nsIDOMHTMLCollection *nscoll = NULL;
    nsresult nsres;

    TRACE("(%p)->(%p)\n", This, p);

    if(!p)
        return E_INVALIDARG;

    *p = NULL;

    if(!This->doc_node->nsdoc) {
        WARN("NULL nsdoc\n");
        return E_UNEXPECTED;
    }

    nsres = nsIDOMHTMLDocument_GetLinks(This->doc_node->nsdoc, &nscoll);
    if(NS_FAILED(nsres)) {
        ERR("GetLinks failed: %08x\n", nsres);
        return E_FAIL;
    }

    if(nscoll) {
        *p = create_collection_from_htmlcol(This->doc_node, (IUnknown*)&This->IHTMLDocument2_iface, nscoll);
        nsIDOMElement_Release(nscoll);
    }

    return S_OK;
}

static HRESULT WINAPI HTMLDocument_get_forms(IHTMLDocument2 *iface, IHTMLElementCollection **p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    nsIDOMHTMLCollection *nscoll = NULL;
    nsresult nsres;

    TRACE("(%p)->(%p)\n", This, p);

    if(!p)
        return E_INVALIDARG;

    *p = NULL;

    if(!This->doc_node->nsdoc) {
        WARN("NULL nsdoc\n");
        return E_UNEXPECTED;
    }

    nsres = nsIDOMHTMLDocument_GetForms(This->doc_node->nsdoc, &nscoll);
    if(NS_FAILED(nsres)) {
        ERR("GetForms failed: %08x\n", nsres);
        return E_FAIL;
    }

    if(nscoll) {
        *p = create_collection_from_htmlcol(This->doc_node, (IUnknown*)&This->IHTMLDocument2_iface, nscoll);
        nsIDOMElement_Release(nscoll);
    }

    return S_OK;
}

static HRESULT WINAPI HTMLDocument_get_anchors(IHTMLDocument2 *iface, IHTMLElementCollection **p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    nsIDOMHTMLCollection *nscoll = NULL;
    nsresult nsres;

    TRACE("(%p)->(%p)\n", This, p);

    if(!p)
        return E_INVALIDARG;

    *p = NULL;

    if(!This->doc_node->nsdoc) {
        WARN("NULL nsdoc\n");
        return E_UNEXPECTED;
    }

    nsres = nsIDOMHTMLDocument_GetAnchors(This->doc_node->nsdoc, &nscoll);
    if(NS_FAILED(nsres)) {
        ERR("GetAnchors failed: %08x\n", nsres);
        return E_FAIL;
    }

    if(nscoll) {
        *p = create_collection_from_htmlcol(This->doc_node, (IUnknown*)&This->IHTMLDocument2_iface, nscoll);
        nsIDOMElement_Release(nscoll);
    }

    return S_OK;
}

static HRESULT WINAPI HTMLDocument_put_title(IHTMLDocument2 *iface, BSTR v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    nsAString nsstr;
    nsresult nsres;

    TRACE("(%p)->(%s)\n", This, debugstr_w(v));

    if(!This->doc_node->nsdoc) {
        WARN("NULL nsdoc\n");
        return E_UNEXPECTED;
    }

    nsAString_InitDepend(&nsstr, v);
    nsres = nsIDOMHTMLDocument_SetTitle(This->doc_node->nsdoc, &nsstr);
    nsAString_Finish(&nsstr);
    if(NS_FAILED(nsres))
        ERR("SetTitle failed: %08x\n", nsres);

    return S_OK;
}

static HRESULT WINAPI HTMLDocument_get_title(IHTMLDocument2 *iface, BSTR *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    const PRUnichar *ret;
    nsAString nsstr;
    nsresult nsres;

    TRACE("(%p)->(%p)\n", This, p);

    if(!This->doc_node->nsdoc) {
        WARN("NULL nsdoc\n");
        return E_UNEXPECTED;
    }


    nsAString_Init(&nsstr, NULL);
    nsres = nsIDOMHTMLDocument_GetTitle(This->doc_node->nsdoc, &nsstr);
    if (NS_SUCCEEDED(nsres)) {
        nsAString_GetData(&nsstr, &ret);
        *p = SysAllocString(ret);
    }
    nsAString_Finish(&nsstr);

    if(NS_FAILED(nsres)) {
        ERR("GetTitle failed: %08x\n", nsres);
        return E_FAIL;
    }

    return S_OK;
}

static HRESULT WINAPI HTMLDocument_get_scripts(IHTMLDocument2 *iface, IHTMLElementCollection **p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_put_designMode(IHTMLDocument2 *iface, BSTR v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%s)\n", This, debugstr_w(v));
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_designMode(IHTMLDocument2 *iface, BSTR *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    static WCHAR szOff[] = {'O','f','f',0};
    FIXME("(%p)->(%p) always returning Off\n", This, p);

    if(!p)
        return E_INVALIDARG;

    *p = SysAllocString(szOff);

    return S_OK;
}

static HRESULT WINAPI HTMLDocument_get_selection(IHTMLDocument2 *iface, IHTMLSelectionObject **p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    nsISelection *nsselection;
    nsresult nsres;

    TRACE("(%p)->(%p)\n", This, p);

    nsres = nsIDOMWindow_GetSelection(This->window->nswindow, &nsselection);
    if(NS_FAILED(nsres)) {
        ERR("GetSelection failed: %08x\n", nsres);
        return E_FAIL;
    }

    return HTMLSelectionObject_Create(This->doc_node, nsselection, p);
}

static HRESULT WINAPI HTMLDocument_get_readyState(IHTMLDocument2 *iface, BSTR *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    static const WCHAR wszUninitialized[] = {'u','n','i','n','i','t','i','a','l','i','z','e','d',0};
    static const WCHAR wszLoading[] = {'l','o','a','d','i','n','g',0};
    static const WCHAR wszLoaded[] = {'l','o','a','d','e','d',0};
    static const WCHAR wszInteractive[] = {'i','n','t','e','r','a','c','t','i','v','e',0};
    static const WCHAR wszComplete[] = {'c','o','m','p','l','e','t','e',0};

    static const LPCWSTR readystate_str[] = {
        wszUninitialized,
        wszLoading,
        wszLoaded,
        wszInteractive,
        wszComplete
    };

    TRACE("(%p)->(%p)\n", iface, p);

    if(!p)
        return E_POINTER;

    *p = SysAllocString(readystate_str[This->window->readystate]);
    return S_OK;
}

static HRESULT WINAPI HTMLDocument_get_frames(IHTMLDocument2 *iface, IHTMLFramesCollection2 **p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_embeds(IHTMLDocument2 *iface, IHTMLElementCollection **p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_plugins(IHTMLDocument2 *iface, IHTMLElementCollection **p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_put_alinkColor(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_alinkColor(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_put_bgColor(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_bgColor(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_put_fgColor(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_fgColor(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_put_linkColor(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->()\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_linkColor(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_put_vlinkColor(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_vlinkColor(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_referrer(IHTMLDocument2 *iface, BSTR *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    FIXME("(%p)->(%p)\n", This, p);

    *p = NULL;
    return S_OK;
 }

static HRESULT WINAPI HTMLDocument_get_location(IHTMLDocument2 *iface, IHTMLLocation **p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%p)\n", This, p);

    if(!This->doc_node->nsdoc) {
        WARN("NULL nsdoc\n");
        return E_UNEXPECTED;
    }

    return IHTMLWindow2_get_location(&This->window->IHTMLWindow2_iface, p);
}

static HRESULT WINAPI HTMLDocument_get_lastModified(IHTMLDocument2 *iface, BSTR *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_put_URL(IHTMLDocument2 *iface, BSTR v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%s)\n", This, debugstr_w(v));
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_URL(IHTMLDocument2 *iface, BSTR *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    static const WCHAR about_blank_url[] =
        {'a','b','o','u','t',':','b','l','a','n','k',0};

    TRACE("(%p)->(%p)\n", iface, p);

    *p = SysAllocString(This->window->url ? This->window->url : about_blank_url);
    return *p ? S_OK : E_OUTOFMEMORY;
}

static HRESULT WINAPI HTMLDocument_put_domain(IHTMLDocument2 *iface, BSTR v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%s)\n", This, debugstr_w(v));
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_domain(IHTMLDocument2 *iface, BSTR *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_put_cookie(IHTMLDocument2 *iface, BSTR v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    BOOL bret;

    TRACE("(%p)->(%s)\n", This, debugstr_w(v));

    bret = InternetSetCookieExW(This->window->url, NULL, v, 0, 0);
    if(!bret) {
        FIXME("InternetSetCookieExW failed: %u\n", GetLastError());
        return HRESULT_FROM_WIN32(GetLastError());
    }

    return S_OK;
}

static HRESULT WINAPI HTMLDocument_get_cookie(IHTMLDocument2 *iface, BSTR *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    DWORD size;
    BOOL bret;

    TRACE("(%p)->(%p)\n", This, p);

    size = 0;
    bret = InternetGetCookieExW(This->window->url, NULL, NULL, &size, 0, NULL);
    if(!bret) {
        switch(GetLastError()) {
        case ERROR_INSUFFICIENT_BUFFER:
            break;
        case ERROR_NO_MORE_ITEMS:
            *p = NULL;
            return S_OK;
        default:
            FIXME("InternetGetCookieExW failed: %u\n", GetLastError());
            return HRESULT_FROM_WIN32(GetLastError());
        }
    }

    if(!size) {
        *p = NULL;
        return S_OK;
    }

    *p = SysAllocStringLen(NULL, size-1);
    if(!*p)
        return E_OUTOFMEMORY;

    bret = InternetGetCookieExW(This->window->url, NULL, *p, &size, 0, NULL);
    if(!bret) {
        ERR("InternetGetCookieExW failed: %u\n", GetLastError());
        return E_FAIL;
    }

    return S_OK;
}

static HRESULT WINAPI HTMLDocument_put_expando(IHTMLDocument2 *iface, VARIANT_BOOL v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%x)\n", This, v);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_expando(IHTMLDocument2 *iface, VARIANT_BOOL *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_put_charset(IHTMLDocument2 *iface, BSTR v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%s)\n", This, debugstr_w(v));
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_charset(IHTMLDocument2 *iface, BSTR *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_put_defaultCharset(IHTMLDocument2 *iface, BSTR v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%s)\n", This, debugstr_w(v));
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_defaultCharset(IHTMLDocument2 *iface, BSTR *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_mimeType(IHTMLDocument2 *iface, BSTR *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_fileSize(IHTMLDocument2 *iface, BSTR *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_fileCreatedDate(IHTMLDocument2 *iface, BSTR *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_fileModifiedDate(IHTMLDocument2 *iface, BSTR *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_fileUpdatedDate(IHTMLDocument2 *iface, BSTR *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_security(IHTMLDocument2 *iface, BSTR *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_protocol(IHTMLDocument2 *iface, BSTR *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_nameProp(IHTMLDocument2 *iface, BSTR *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT document_write(HTMLDocument *This, SAFEARRAY *psarray, BOOL ln)
{
    nsAString nsstr;
    VARIANT *var;
    ULONG i, argc;
    nsresult nsres;
    HRESULT hres;

    if(!This->doc_node->nsdoc) {
        WARN("NULL nsdoc\n");
        return E_UNEXPECTED;
    }

    if (!psarray)
        return S_OK;

    if(psarray->cDims != 1) {
        FIXME("cDims=%d\n", psarray->cDims);
        return E_INVALIDARG;
    }

    hres = SafeArrayAccessData(psarray, (void**)&var);
    if(FAILED(hres)) {
        WARN("SafeArrayAccessData failed: %08x\n", hres);
        return hres;
    }

    nsAString_Init(&nsstr, NULL);

    argc = psarray->rgsabound[0].cElements;
    for(i=0; i < argc; i++) {
        if(V_VT(var+i) == VT_BSTR) {
            nsAString_SetData(&nsstr, V_BSTR(var+i));
            if(!ln || i != argc-1)
                nsres = nsIDOMHTMLDocument_Write(This->doc_node->nsdoc, &nsstr);
            else
                nsres = nsIDOMHTMLDocument_Writeln(This->doc_node->nsdoc, &nsstr);
            if(NS_FAILED(nsres))
                ERR("Write failed: %08x\n", nsres);
        }else {
            FIXME("vt=%d\n", V_VT(var+i));
        }
    }

    nsAString_Finish(&nsstr);
    SafeArrayUnaccessData(psarray);

    return S_OK;
}

static HRESULT WINAPI HTMLDocument_write(IHTMLDocument2 *iface, SAFEARRAY *psarray)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%p)\n", iface, psarray);

    return document_write(This, psarray, FALSE);
}

static HRESULT WINAPI HTMLDocument_writeln(IHTMLDocument2 *iface, SAFEARRAY *psarray)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%p)\n", This, psarray);

    return document_write(This, psarray, TRUE);
}

static HRESULT WINAPI HTMLDocument_open(IHTMLDocument2 *iface, BSTR url, VARIANT name,
                        VARIANT features, VARIANT replace, IDispatch **pomWindowResult)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    nsresult nsres;

    static const WCHAR text_htmlW[] = {'t','e','x','t','/','h','t','m','l',0};

    TRACE("(%p)->(%s %s %s %s %p)\n", This, debugstr_w(url), debugstr_variant(&name),
          debugstr_variant(&features), debugstr_variant(&replace), pomWindowResult);

    if(!This->doc_node->nsdoc) {
        ERR("!nsdoc\n");
        return E_NOTIMPL;
    }

    if(!url || strcmpW(url, text_htmlW) || V_VT(&name) != VT_ERROR
       || V_VT(&features) != VT_ERROR || V_VT(&replace) != VT_ERROR)
        FIXME("unsupported args\n");

    nsres = nsIDOMHTMLDocument_Open(This->doc_node->nsdoc);
    if(NS_FAILED(nsres)) {
        ERR("Open failed: %08x\n", nsres);
        return E_FAIL;
    }

    *pomWindowResult = (IDispatch*)&This->window->IHTMLWindow2_iface;
    IHTMLWindow2_AddRef(&This->window->IHTMLWindow2_iface);
    return S_OK;
}

static HRESULT WINAPI HTMLDocument_close(IHTMLDocument2 *iface)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    nsresult nsres;

    TRACE("(%p)\n", This);

    if(!This->doc_node->nsdoc) {
        ERR("!nsdoc\n");
        return E_NOTIMPL;
    }

    nsres = nsIDOMHTMLDocument_Close(This->doc_node->nsdoc);
    if(NS_FAILED(nsres)) {
        ERR("Close failed: %08x\n", nsres);
        return E_FAIL;
    }

    return S_OK;
}

static HRESULT WINAPI HTMLDocument_clear(IHTMLDocument2 *iface)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    nsIDOMNSHTMLDocument *nsdoc;
    nsresult nsres;

    TRACE("(%p)\n", This);

    nsres = nsIDOMHTMLDocument_QueryInterface(This->doc_node->nsdoc, &IID_nsIDOMNSHTMLDocument, (void**)&nsdoc);
    if(NS_FAILED(nsres)) {
        ERR("Could not get nsIDOMNSHTMLDocument iface: %08x\n", nsres);
        return E_FAIL;
    }

    nsres = nsIDOMNSHTMLDocument_Clear(nsdoc);
    nsIDOMNSHTMLDocument_Release(nsdoc);
    if(NS_FAILED(nsres)) {
        ERR("Clear failed: %08x\n", nsres);
        return E_FAIL;
    }

    return S_OK;
}

static HRESULT WINAPI HTMLDocument_queryCommandSupported(IHTMLDocument2 *iface, BSTR cmdID,
                                                        VARIANT_BOOL *pfRet)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%s %p)\n", This, debugstr_w(cmdID), pfRet);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_queryCommandEnabled(IHTMLDocument2 *iface, BSTR cmdID,
                                                        VARIANT_BOOL *pfRet)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%s %p)\n", This, debugstr_w(cmdID), pfRet);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_queryCommandState(IHTMLDocument2 *iface, BSTR cmdID,
                                                        VARIANT_BOOL *pfRet)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%s %p)\n", This, debugstr_w(cmdID), pfRet);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_queryCommandIndeterm(IHTMLDocument2 *iface, BSTR cmdID,
                                                        VARIANT_BOOL *pfRet)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%s %p)\n", This, debugstr_w(cmdID), pfRet);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_queryCommandText(IHTMLDocument2 *iface, BSTR cmdID,
                                                        BSTR *pfRet)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%s %p)\n", This, debugstr_w(cmdID), pfRet);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_queryCommandValue(IHTMLDocument2 *iface, BSTR cmdID,
                                                        VARIANT *pfRet)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%s %p)\n", This, debugstr_w(cmdID), pfRet);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_execCommand(IHTMLDocument2 *iface, BSTR cmdID,
                                VARIANT_BOOL showUI, VARIANT value, VARIANT_BOOL *pfRet)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%s %x %p)\n", This, debugstr_w(cmdID), showUI, pfRet);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_execCommandShowHelp(IHTMLDocument2 *iface, BSTR cmdID,
                                                        VARIANT_BOOL *pfRet)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%s %p)\n", This, debugstr_w(cmdID), pfRet);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_createElement(IHTMLDocument2 *iface, BSTR eTag,
                                                 IHTMLElement **newElem)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    nsIDOMHTMLElement *nselem;
    HTMLElement *elem;
    HRESULT hres;

    TRACE("(%p)->(%s %p)\n", This, debugstr_w(eTag), newElem);

    hres = create_nselem(This->doc_node, eTag, &nselem);
    if(FAILED(hres))
        return hres;

    hres = HTMLElement_Create(This->doc_node, (nsIDOMNode*)nselem, TRUE, &elem);
    nsIDOMHTMLElement_Release(nselem);
    if(FAILED(hres))
        return hres;

    *newElem = &elem->IHTMLElement_iface;
    IHTMLElement_AddRef(&elem->IHTMLElement_iface);
    return S_OK;
}

static HRESULT WINAPI HTMLDocument_put_onhelp(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_onhelp(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_put_onclick(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%s)\n", This, debugstr_variant(&v));

    return set_doc_event(This, EVENTID_CLICK, &v);
}

static HRESULT WINAPI HTMLDocument_get_onclick(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%p)\n", This, p);

    return get_doc_event(This, EVENTID_CLICK, p);
}

static HRESULT WINAPI HTMLDocument_put_ondblclick(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_ondblclick(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_put_onkeyup(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%s)\n", This, debugstr_variant(&v));

    return set_doc_event(This, EVENTID_KEYUP, &v);
}

static HRESULT WINAPI HTMLDocument_get_onkeyup(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%p)\n", This, p);

    return get_doc_event(This, EVENTID_KEYUP, p);
}

static HRESULT WINAPI HTMLDocument_put_onkeydown(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%s)\n", This, debugstr_variant(&v));

    return set_doc_event(This, EVENTID_KEYDOWN, &v);
}

static HRESULT WINAPI HTMLDocument_get_onkeydown(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%p)\n", This, p);

    return get_doc_event(This, EVENTID_KEYDOWN, p);
}

static HRESULT WINAPI HTMLDocument_put_onkeypress(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_onkeypress(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_put_onmouseup(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%s)\n", This, debugstr_variant(&v));

    return set_doc_event(This, EVENTID_MOUSEUP, &v);
}

static HRESULT WINAPI HTMLDocument_get_onmouseup(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%p)\n", This, p);

    return get_doc_event(This, EVENTID_MOUSEUP, p);
}

static HRESULT WINAPI HTMLDocument_put_onmousedown(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->()\n", This);

    return set_doc_event(This, EVENTID_MOUSEDOWN, &v);
}

static HRESULT WINAPI HTMLDocument_get_onmousedown(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%p)\n", This, p);

    return get_doc_event(This, EVENTID_MOUSEDOWN, p);
}

static HRESULT WINAPI HTMLDocument_put_onmousemove(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->()\n", This);

    return set_doc_event(This, EVENTID_MOUSEMOVE, &v);
}

static HRESULT WINAPI HTMLDocument_get_onmousemove(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%p)\n", This, p);

    return get_doc_event(This, EVENTID_MOUSEMOVE, p);
}

static HRESULT WINAPI HTMLDocument_put_onmouseout(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%s)\n", This, debugstr_variant(&v));

    return set_doc_event(This, EVENTID_MOUSEOUT, &v);
}

static HRESULT WINAPI HTMLDocument_get_onmouseout(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%p)\n", This, p);

    return get_doc_event(This, EVENTID_MOUSEOUT, p);
}

static HRESULT WINAPI HTMLDocument_put_onmouseover(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)\n", This);

    return set_doc_event(This, EVENTID_MOUSEOVER, &v);
}

static HRESULT WINAPI HTMLDocument_get_onmouseover(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%p)\n", This, p);

    return get_doc_event(This, EVENTID_MOUSEOVER, p);
}

static HRESULT WINAPI HTMLDocument_put_onreadystatechange(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%s)\n", This, debugstr_variant(&v));

    return set_doc_event(This, EVENTID_READYSTATECHANGE, &v);
}

static HRESULT WINAPI HTMLDocument_get_onreadystatechange(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%p)\n", This, p);

    return get_doc_event(This, EVENTID_READYSTATECHANGE, p);
}

static HRESULT WINAPI HTMLDocument_put_onafterupdate(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_onafterupdate(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_put_onrowexit(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_onrowexit(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_put_onrowenter(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_onrowenter(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_put_ondragstart(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%s)\n", This, debugstr_variant(&v));

    return set_doc_event(This, EVENTID_DRAGSTART, &v);
}

static HRESULT WINAPI HTMLDocument_get_ondragstart(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%p)\n", This, p);

    return get_doc_event(This, EVENTID_DRAGSTART, p);
}

static HRESULT WINAPI HTMLDocument_put_onselectstart(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%s)\n", This, debugstr_variant(&v));

    return set_doc_event(This, EVENTID_SELECTSTART, &v);
}

static HRESULT WINAPI HTMLDocument_get_onselectstart(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%p)\n", This, p);

    return get_doc_event(This, EVENTID_SELECTSTART, p);
}

static HRESULT WINAPI HTMLDocument_elementFromPoint(IHTMLDocument2 *iface, LONG x, LONG y,
                                                        IHTMLElement **elementHit)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%d %d %p)\n", This, x, y, elementHit);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_parentWindow(IHTMLDocument2 *iface, IHTMLWindow2 **p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    TRACE("(%p)->(%p)\n", This, p);

    *p = &This->window->IHTMLWindow2_iface;
    IHTMLWindow2_AddRef(*p);
    return S_OK;
}

static HRESULT WINAPI HTMLDocument_get_styleSheets(IHTMLDocument2 *iface,
                                                   IHTMLStyleSheetsCollection **p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    nsIDOMStyleSheetList *nsstylelist;
    nsIDOMDocumentStyle *nsdocstyle;
    nsresult nsres;

    TRACE("(%p)->(%p)\n", This, p);

    *p = NULL;

    if(!This->doc_node->nsdoc) {
        WARN("NULL nsdoc\n");
        return E_UNEXPECTED;
    }

    nsIDOMHTMLDocument_QueryInterface(This->doc_node->nsdoc, &IID_nsIDOMDocumentStyle, (void**)&nsdocstyle);
    nsres = nsIDOMDocumentStyle_GetStyleSheets(nsdocstyle, &nsstylelist);
    nsIDOMDocumentStyle_Release(nsdocstyle);
    if(NS_FAILED(nsres)) {
        ERR("GetStyleSheets failed: %08x\n", nsres);
        return E_FAIL;
    }

    *p = HTMLStyleSheetsCollection_Create(nsstylelist);
    nsIDOMDocumentStyle_Release(nsstylelist);

    return S_OK;
}

static HRESULT WINAPI HTMLDocument_put_onbeforeupdate(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_onbeforeupdate(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_put_onerrorupdate(IHTMLDocument2 *iface, VARIANT v)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_get_onerrorupdate(IHTMLDocument2 *iface, VARIANT *p)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_toString(IHTMLDocument2 *iface, BSTR *String)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);
    FIXME("(%p)->(%p)\n", This, String);
    return E_NOTIMPL;
}

static HRESULT WINAPI HTMLDocument_createStyleSheet(IHTMLDocument2 *iface, BSTR bstrHref,
                                            LONG lIndex, IHTMLStyleSheet **ppnewStyleSheet)
{
    HTMLDocument *This = impl_from_IHTMLDocument2(iface);

    FIXME("(%p)->(%s %d %p) semi-stub\n", This, debugstr_w(bstrHref), lIndex, ppnewStyleSheet);

    *ppnewStyleSheet = HTMLStyleSheet_Create(NULL);
    return S_OK;
}

static const IHTMLDocument2Vtbl HTMLDocumentVtbl = {
    HTMLDocument_QueryInterface,
    HTMLDocument_AddRef,
    HTMLDocument_Release,
    HTMLDocument_GetTypeInfoCount,
    HTMLDocument_GetTypeInfo,
    HTMLDocument_GetIDsOfNames,
    HTMLDocument_Invoke,
    HTMLDocument_get_Script,
    HTMLDocument_get_all,
    HTMLDocument_get_body,
    HTMLDocument_get_activeElement,
    HTMLDocument_get_images,
    HTMLDocument_get_applets,
    HTMLDocument_get_links,
    HTMLDocument_get_forms,
    HTMLDocument_get_anchors,
    HTMLDocument_put_title,
    HTMLDocument_get_title,
    HTMLDocument_get_scripts,
    HTMLDocument_put_designMode,
    HTMLDocument_get_designMode,
    HTMLDocument_get_selection,
    HTMLDocument_get_readyState,
    HTMLDocument_get_frames,
    HTMLDocument_get_embeds,
    HTMLDocument_get_plugins,
    HTMLDocument_put_alinkColor,
    HTMLDocument_get_alinkColor,
    HTMLDocument_put_bgColor,
    HTMLDocument_get_bgColor,
    HTMLDocument_put_fgColor,
    HTMLDocument_get_fgColor,
    HTMLDocument_put_linkColor,
    HTMLDocument_get_linkColor,
    HTMLDocument_put_vlinkColor,
    HTMLDocument_get_vlinkColor,
    HTMLDocument_get_referrer,
    HTMLDocument_get_location,
    HTMLDocument_get_lastModified,
    HTMLDocument_put_URL,
    HTMLDocument_get_URL,
    HTMLDocument_put_domain,
    HTMLDocument_get_domain,
    HTMLDocument_put_cookie,
    HTMLDocument_get_cookie,
    HTMLDocument_put_expando,
    HTMLDocument_get_expando,
    HTMLDocument_put_charset,
    HTMLDocument_get_charset,
    HTMLDocument_put_defaultCharset,
    HTMLDocument_get_defaultCharset,
    HTMLDocument_get_mimeType,
    HTMLDocument_get_fileSize,
    HTMLDocument_get_fileCreatedDate,
    HTMLDocument_get_fileModifiedDate,
    HTMLDocument_get_fileUpdatedDate,
    HTMLDocument_get_security,
    HTMLDocument_get_protocol,
    HTMLDocument_get_nameProp,
    HTMLDocument_write,
    HTMLDocument_writeln,
    HTMLDocument_open,
    HTMLDocument_close,
    HTMLDocument_clear,
    HTMLDocument_queryCommandSupported,
    HTMLDocument_queryCommandEnabled,
    HTMLDocument_queryCommandState,
    HTMLDocument_queryCommandIndeterm,
    HTMLDocument_queryCommandText,
    HTMLDocument_queryCommandValue,
    HTMLDocument_execCommand,
    HTMLDocument_execCommandShowHelp,
    HTMLDocument_createElement,
    HTMLDocument_put_onhelp,
    HTMLDocument_get_onhelp,
    HTMLDocument_put_onclick,
    HTMLDocument_get_onclick,
    HTMLDocument_put_ondblclick,
    HTMLDocument_get_ondblclick,
    HTMLDocument_put_onkeyup,
    HTMLDocument_get_onkeyup,
    HTMLDocument_put_onkeydown,
    HTMLDocument_get_onkeydown,
    HTMLDocument_put_onkeypress,
    HTMLDocument_get_onkeypress,
    HTMLDocument_put_onmouseup,
    HTMLDocument_get_onmouseup,
    HTMLDocument_put_onmousedown,
    HTMLDocument_get_onmousedown,
    HTMLDocument_put_onmousemove,
    HTMLDocument_get_onmousemove,
    HTMLDocument_put_onmouseout,
    HTMLDocument_get_onmouseout,
    HTMLDocument_put_onmouseover,
    HTMLDocument_get_onmouseover,
    HTMLDocument_put_onreadystatechange,
    HTMLDocument_get_onreadystatechange,
    HTMLDocument_put_onafterupdate,
    HTMLDocument_get_onafterupdate,
    HTMLDocument_put_onrowexit,
    HTMLDocument_get_onrowexit,
    HTMLDocument_put_onrowenter,
    HTMLDocument_get_onrowenter,
    HTMLDocument_put_ondragstart,
    HTMLDocument_get_ondragstart,
    HTMLDocument_put_onselectstart,
    HTMLDocument_get_onselectstart,
    HTMLDocument_elementFromPoint,
    HTMLDocument_get_parentWindow,
    HTMLDocument_get_styleSheets,
    HTMLDocument_put_onbeforeupdate,
    HTMLDocument_get_onbeforeupdate,
    HTMLDocument_put_onerrorupdate,
    HTMLDocument_get_onerrorupdate,
    HTMLDocument_toString,
    HTMLDocument_createStyleSheet
};

static void HTMLDocument_on_advise(IUnknown *iface, cp_static_data_t *cp)
{
    HTMLDocument *This = impl_from_IHTMLDocument2((IHTMLDocument2*)iface);

    if(This->window)
        update_cp_events(This->window, &This->doc_node->node.event_target, cp, This->doc_node->node.nsnode);
}

static inline HTMLDocument *impl_from_ISupportErrorInfo(ISupportErrorInfo *iface)
{
    return CONTAINING_RECORD(iface, HTMLDocument, ISupportErrorInfo_iface);
}

static HRESULT WINAPI SupportErrorInfo_QueryInterface(ISupportErrorInfo *iface, REFIID riid, void **ppv)
{
    HTMLDocument *This = impl_from_ISupportErrorInfo(iface);
    return htmldoc_query_interface(This, riid, ppv);
}

static ULONG WINAPI SupportErrorInfo_AddRef(ISupportErrorInfo *iface)
{
    HTMLDocument *This = impl_from_ISupportErrorInfo(iface);
    return htmldoc_addref(This);
}

static ULONG WINAPI SupportErrorInfo_Release(ISupportErrorInfo *iface)
{
    HTMLDocument *This = impl_from_ISupportErrorInfo(iface);
    return htmldoc_release(This);
}

static HRESULT WINAPI SupportErrorInfo_InterfaceSupportsErrorInfo(ISupportErrorInfo *iface, REFIID riid)
{
    FIXME("(%p)->(%s)\n", iface, debugstr_guid(riid));
    return S_FALSE;
}

static const ISupportErrorInfoVtbl SupportErrorInfoVtbl = {
    SupportErrorInfo_QueryInterface,
    SupportErrorInfo_AddRef,
    SupportErrorInfo_Release,
    SupportErrorInfo_InterfaceSupportsErrorInfo
};

static inline HTMLDocument *impl_from_IDispatchEx(IDispatchEx *iface)
{
    return CONTAINING_RECORD(iface, HTMLDocument, IDispatchEx_iface);
}

static HRESULT WINAPI DocDispatchEx_QueryInterface(IDispatchEx *iface, REFIID riid, void **ppv)
{
    HTMLDocument *This = impl_from_IDispatchEx(iface);

    return htmldoc_query_interface(This, riid, ppv);
}

static ULONG WINAPI DocDispatchEx_AddRef(IDispatchEx *iface)
{
    HTMLDocument *This = impl_from_IDispatchEx(iface);

    return htmldoc_addref(This);
}

static ULONG WINAPI DocDispatchEx_Release(IDispatchEx *iface)
{
    HTMLDocument *This = impl_from_IDispatchEx(iface);

    return htmldoc_release(This);
}

static HRESULT WINAPI DocDispatchEx_GetTypeInfoCount(IDispatchEx *iface, UINT *pctinfo)
{
    HTMLDocument *This = impl_from_IDispatchEx(iface);

    return IDispatchEx_GetTypeInfoCount(This->dispex, pctinfo);
}

static HRESULT WINAPI DocDispatchEx_GetTypeInfo(IDispatchEx *iface, UINT iTInfo,
                                               LCID lcid, ITypeInfo **ppTInfo)
{
    HTMLDocument *This = impl_from_IDispatchEx(iface);

    return IDispatchEx_GetTypeInfo(This->dispex, iTInfo, lcid, ppTInfo);
}

static HRESULT WINAPI DocDispatchEx_GetIDsOfNames(IDispatchEx *iface, REFIID riid,
                                                 LPOLESTR *rgszNames, UINT cNames,
                                                 LCID lcid, DISPID *rgDispId)
{
    HTMLDocument *This = impl_from_IDispatchEx(iface);

    return IDispatchEx_GetIDsOfNames(This->dispex, riid, rgszNames, cNames, lcid, rgDispId);
}

static HRESULT WINAPI DocDispatchEx_Invoke(IDispatchEx *iface, DISPID dispIdMember,
                            REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams,
                            VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
    HTMLDocument *This = impl_from_IDispatchEx(iface);

    TRACE("(%p)->(%d %s %d %d %p %p %p %p)\n", This, dispIdMember, debugstr_guid(riid),
          lcid, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);

    switch(dispIdMember) {
    case DISPID_READYSTATE:
        TRACE("DISPID_READYSTATE\n");

        if(!(wFlags & DISPATCH_PROPERTYGET))
            return E_INVALIDARG;

        V_VT(pVarResult) = VT_I4;
        V_I4(pVarResult) = This->window->readystate;
        return S_OK;
    }

    return IDispatchEx_Invoke(This->dispex, dispIdMember, riid, lcid, wFlags, pDispParams,
                              pVarResult, pExcepInfo, puArgErr);
}

static HRESULT WINAPI DocDispatchEx_GetDispID(IDispatchEx *iface, BSTR bstrName, DWORD grfdex, DISPID *pid)
{
    HTMLDocument *This = impl_from_IDispatchEx(iface);

    return IDispatchEx_GetDispID(This->dispex, bstrName, grfdex, pid);
}

static HRESULT WINAPI DocDispatchEx_InvokeEx(IDispatchEx *iface, DISPID id, LCID lcid, WORD wFlags, DISPPARAMS *pdp,
        VARIANT *pvarRes, EXCEPINFO *pei, IServiceProvider *pspCaller)
{
    HTMLDocument *This = impl_from_IDispatchEx(iface);

    if(This->window && id == DISPID_IHTMLDOCUMENT2_LOCATION && (wFlags & DISPATCH_PROPERTYPUT))
        return IDispatchEx_InvokeEx(&This->window->IDispatchEx_iface, DISPID_IHTMLWINDOW2_LOCATION,
                lcid, wFlags, pdp, pvarRes, pei, pspCaller);


    return IDispatchEx_InvokeEx(This->dispex, id, lcid, wFlags, pdp, pvarRes, pei, pspCaller);
}

static HRESULT WINAPI DocDispatchEx_DeleteMemberByName(IDispatchEx *iface, BSTR bstrName, DWORD grfdex)
{
    HTMLDocument *This = impl_from_IDispatchEx(iface);

    return IDispatchEx_DeleteMemberByName(This->dispex, bstrName, grfdex);
}

static HRESULT WINAPI DocDispatchEx_DeleteMemberByDispID(IDispatchEx *iface, DISPID id)
{
    HTMLDocument *This = impl_from_IDispatchEx(iface);

    return IDispatchEx_DeleteMemberByDispID(This->dispex, id);
}

static HRESULT WINAPI DocDispatchEx_GetMemberProperties(IDispatchEx *iface, DISPID id, DWORD grfdexFetch, DWORD *pgrfdex)
{
    HTMLDocument *This = impl_from_IDispatchEx(iface);

    return IDispatchEx_GetMemberProperties(This->dispex, id, grfdexFetch, pgrfdex);
}

static HRESULT WINAPI DocDispatchEx_GetMemberName(IDispatchEx *iface, DISPID id, BSTR *pbstrName)
{
    HTMLDocument *This = impl_from_IDispatchEx(iface);

    return IDispatchEx_GetMemberName(This->dispex, id, pbstrName);
}

static HRESULT WINAPI DocDispatchEx_GetNextDispID(IDispatchEx *iface, DWORD grfdex, DISPID id, DISPID *pid)
{
    HTMLDocument *This = impl_from_IDispatchEx(iface);

    return IDispatchEx_GetNextDispID(This->dispex, grfdex, id, pid);
}

static HRESULT WINAPI DocDispatchEx_GetNameSpaceParent(IDispatchEx *iface, IUnknown **ppunk)
{
    HTMLDocument *This = impl_from_IDispatchEx(iface);

    return IDispatchEx_GetNameSpaceParent(This->dispex, ppunk);
}

static const IDispatchExVtbl DocDispatchExVtbl = {
    DocDispatchEx_QueryInterface,
    DocDispatchEx_AddRef,
    DocDispatchEx_Release,
    DocDispatchEx_GetTypeInfoCount,
    DocDispatchEx_GetTypeInfo,
    DocDispatchEx_GetIDsOfNames,
    DocDispatchEx_Invoke,
    DocDispatchEx_GetDispID,
    DocDispatchEx_InvokeEx,
    DocDispatchEx_DeleteMemberByName,
    DocDispatchEx_DeleteMemberByDispID,
    DocDispatchEx_GetMemberProperties,
    DocDispatchEx_GetMemberName,
    DocDispatchEx_GetNextDispID,
    DocDispatchEx_GetNameSpaceParent
};

static BOOL htmldoc_qi(HTMLDocument *This, REFIID riid, void **ppv)
{
    *ppv = NULL;

    if(IsEqualGUID(&IID_IUnknown, riid)) {
        TRACE("(%p)->(IID_IUnknown, %p)\n", This, ppv);
        *ppv = &This->IHTMLDocument2_iface;
    }else if(IsEqualGUID(&IID_IDispatch, riid)) {
        TRACE("(%p)->(IID_IDispatch, %p)\n", This, ppv);
        *ppv = &This->IDispatchEx_iface;
    }else if(IsEqualGUID(&IID_IDispatchEx, riid)) {
        TRACE("(%p)->(IID_IDispatchEx, %p)\n", This, ppv);
        *ppv = &This->IDispatchEx_iface;
    }else if(IsEqualGUID(&IID_IHTMLDocument, riid)) {
        TRACE("(%p)->(IID_IHTMLDocument, %p)\n", This, ppv);
        *ppv = &This->IHTMLDocument2_iface;
    }else if(IsEqualGUID(&IID_IHTMLDocument2, riid)) {
        TRACE("(%p)->(IID_IHTMLDocument2, %p)\n", This, ppv);
        *ppv = &This->IHTMLDocument2_iface;
    }else if(IsEqualGUID(&IID_IHTMLDocument3, riid)) {
        TRACE("(%p)->(IID_IHTMLDocument3, %p)\n", This, ppv);
        *ppv = &This->IHTMLDocument3_iface;
    }else if(IsEqualGUID(&IID_IHTMLDocument4, riid)) {
        TRACE("(%p)->(IID_IHTMLDocument4, %p)\n", This, ppv);
        *ppv = &This->IHTMLDocument4_iface;
    }else if(IsEqualGUID(&IID_IHTMLDocument5, riid)) {
        TRACE("(%p)->(IID_IHTMLDocument5, %p)\n", This, ppv);
        *ppv = &This->IHTMLDocument5_iface;
    }else if(IsEqualGUID(&IID_IHTMLDocument6, riid)) {
        TRACE("(%p)->(IID_IHTMLDocument6, %p)\n", This, ppv);
        *ppv = &This->IHTMLDocument6_iface;
    }else if(IsEqualGUID(&IID_IPersist, riid)) {
        TRACE("(%p)->(IID_IPersist, %p)\n", This, ppv);
        *ppv = &This->IPersistFile_iface;
    }else if(IsEqualGUID(&IID_IPersistMoniker, riid)) {
        TRACE("(%p)->(IID_IPersistMoniker, %p)\n", This, ppv);
        *ppv = &This->IPersistMoniker_iface;
    }else if(IsEqualGUID(&IID_IPersistFile, riid)) {
        TRACE("(%p)->(IID_IPersistFile, %p)\n", This, ppv);
        *ppv = &This->IPersistFile_iface;
    }else if(IsEqualGUID(&IID_IMonikerProp, riid)) {
        TRACE("(%p)->(IID_IMonikerProp, %p)\n", This, ppv);
        *ppv = &This->IMonikerProp_iface;
    }else if(IsEqualGUID(&IID_IOleObject, riid)) {
        TRACE("(%p)->(IID_IOleObject, %p)\n", This, ppv);
        *ppv = &This->IOleObject_iface;
    }else if(IsEqualGUID(&IID_IOleDocument, riid)) {
        TRACE("(%p)->(IID_IOleDocument, %p)\n", This, ppv);
        *ppv = &This->IOleDocument_iface;
    }else if(IsEqualGUID(&IID_IOleDocumentView, riid)) {
        TRACE("(%p)->(IID_IOleDocumentView, %p)\n", This, ppv);
        *ppv = &This->IOleDocumentView_iface;
    }else if(IsEqualGUID(&IID_IOleInPlaceActiveObject, riid)) {
        TRACE("(%p)->(IID_IOleInPlaceActiveObject, %p)\n", This, ppv);
        *ppv = &This->IOleInPlaceActiveObject_iface;
    }else if(IsEqualGUID(&IID_IViewObject, riid)) {
        TRACE("(%p)->(IID_IViewObject, %p)\n", This, ppv);
        *ppv = &This->IViewObjectEx_iface;
    }else if(IsEqualGUID(&IID_IViewObject2, riid)) {
        TRACE("(%p)->(IID_IViewObject2, %p)\n", This, ppv);
        *ppv = &This->IViewObjectEx_iface;
    }else if(IsEqualGUID(&IID_IViewObjectEx, riid)) {
        TRACE("(%p)->(IID_IViewObjectEx, %p)\n", This, ppv);
        *ppv = &This->IViewObjectEx_iface;
    }else if(IsEqualGUID(&IID_IOleWindow, riid)) {
        TRACE("(%p)->(IID_IOleWindow, %p)\n", This, ppv);
        *ppv = &This->IOleInPlaceActiveObject_iface;
    }else if(IsEqualGUID(&IID_IOleInPlaceObject, riid)) {
        TRACE("(%p)->(IID_IOleInPlaceObject, %p)\n", This, ppv);
        *ppv = &This->IOleInPlaceObjectWindowless_iface;
    }else if(IsEqualGUID(&IID_IOleInPlaceObjectWindowless, riid)) {
        TRACE("(%p)->(IID_IOleInPlaceObjectWindowless, %p)\n", This, ppv);
        *ppv = &This->IOleInPlaceObjectWindowless_iface;
    }else if(IsEqualGUID(&IID_IServiceProvider, riid)) {
        TRACE("(%p)->(IID_IServiceProvider, %p)\n", This, ppv);
        *ppv = &This->IServiceProvider_iface;
    }else if(IsEqualGUID(&IID_IOleCommandTarget, riid)) {
        TRACE("(%p)->(IID_IOleCommandTarget, %p)\n", This, ppv);
        *ppv = &This->IOleCommandTarget_iface;
    }else if(IsEqualGUID(&IID_IOleControl, riid)) {
        TRACE("(%p)->(IID_IOleControl, %p)\n", This, ppv);
        *ppv = &This->IOleControl_iface;
    }else if(IsEqualGUID(&IID_IHlinkTarget, riid)) {
        TRACE("(%p)->(IID_IHlinkTarget, %p)\n", This, ppv);
        *ppv = &This->IHlinkTarget_iface;
    }else if(IsEqualGUID(&IID_IConnectionPointContainer, riid)) {
        TRACE("(%p)->(IID_IConnectionPointContainer %p)\n", This, ppv);
        *ppv = &This->cp_container.IConnectionPointContainer_iface;
    }else if(IsEqualGUID(&IID_IPersistStreamInit, riid)) {
        TRACE("(%p)->(IID_IPersistStreamInit %p)\n", This, ppv);
        *ppv = &This->IPersistStreamInit_iface;
    }else if(IsEqualGUID(&DIID_DispHTMLDocument, riid)) {
        TRACE("(%p)->(DIID_DispHTMLDocument %p)\n", This, ppv);
        *ppv = &This->IHTMLDocument2_iface;
    }else if(IsEqualGUID(&IID_ISupportErrorInfo, riid)) {
        TRACE("(%p)->(IID_ISupportErrorInfo %p)\n", This, ppv);
        *ppv = &This->ISupportErrorInfo_iface;
    }else if(IsEqualGUID(&IID_IPersistHistory, riid)) {
        TRACE("(%p)->(IID_IPersistHistory %p)\n", This, ppv);
        *ppv = &This->IPersistHistory_iface;
    }else if(IsEqualGUID(&CLSID_CMarkup, riid)) {
        FIXME("(%p)->(CLSID_CMarkup %p)\n", This, ppv);
        *ppv = NULL;
    }else if(IsEqualGUID(&IID_IRunnableObject, riid)) {
        TRACE("(%p)->(IID_IRunnableObject %p) returning NULL\n", This, ppv);
        *ppv = NULL;
    }else if(IsEqualGUID(&IID_IPersistPropertyBag, riid)) {
        TRACE("(%p)->(IID_IPersistPropertyBag %p) returning NULL\n", This, ppv);
        *ppv = NULL;
    }else if(IsEqualGUID(&IID_IMarshal, riid)) {
        TRACE("(%p)->(IID_IMarshal %p) returning NULL\n", This, ppv);
        *ppv = NULL;
    }else if(IsEqualGUID(&IID_IExternalConnection, riid)) {
        TRACE("(%p)->(IID_IExternalConnection %p) returning NULL\n", This, ppv);
        *ppv = NULL;
    }else if(IsEqualGUID(&IID_IStdMarshalInfo, riid)) {
        TRACE("(%p)->(IID_IStdMarshalInfo %p) returning NULL\n", This, ppv);
        *ppv = NULL;
    }else if(IsEqualGUID(&IID_IObjectWithSite, riid)) {
        TRACE("(%p)->(IID_IObjectWithSite %p)\n", This, ppv);
        *ppv = &This->IObjectWithSite_iface;
    }else if(IsEqualGUID(&IID_IOleContainer, riid)) {
        TRACE("(%p)->(IID_IOleContainer %p)\n", This, ppv);
        *ppv = &This->IOleContainer_iface;
    }else if(IsEqualGUID(&IID_IObjectSafety, riid)) {
        TRACE("(%p)->(IID_IObjectSafety %p)\n", This, ppv);
        *ppv = &This->IObjectSafety_iface;
    }else {
        return FALSE;
    }

    if(*ppv)
        IUnknown_AddRef((IUnknown*)*ppv);
    return TRUE;
}

static cp_static_data_t HTMLDocumentEvents_data = { HTMLDocumentEvents_tid, HTMLDocument_on_advise };

static void init_doc(HTMLDocument *doc, IUnknown *unk_impl, IDispatchEx *dispex)
{
    doc->IHTMLDocument2_iface.lpVtbl = &HTMLDocumentVtbl;
    doc->IDispatchEx_iface.lpVtbl = &DocDispatchExVtbl;
    doc->ISupportErrorInfo_iface.lpVtbl = &SupportErrorInfoVtbl;

    doc->unk_impl = unk_impl;
    doc->dispex = dispex;
    doc->task_magic = get_task_target_magic();

    HTMLDocument_HTMLDocument3_Init(doc);
    HTMLDocument_HTMLDocument5_Init(doc);
    HTMLDocument_Persist_Init(doc);
    HTMLDocument_OleCmd_Init(doc);
    HTMLDocument_OleObj_Init(doc);
    HTMLDocument_View_Init(doc);
    HTMLDocument_Window_Init(doc);
    HTMLDocument_Service_Init(doc);
    HTMLDocument_Hlink_Init(doc);

    ConnectionPointContainer_Init(&doc->cp_container, (IUnknown*)&doc->IHTMLDocument2_iface);
    ConnectionPoint_Init(&doc->cp_dispatch, &doc->cp_container, &IID_IDispatch, &HTMLDocumentEvents_data);
    ConnectionPoint_Init(&doc->cp_propnotif, &doc->cp_container, &IID_IPropertyNotifySink, NULL);
    ConnectionPoint_Init(&doc->cp_htmldocevents, &doc->cp_container, &DIID_HTMLDocumentEvents, &HTMLDocumentEvents_data);
    ConnectionPoint_Init(&doc->cp_htmldocevents2, &doc->cp_container, &DIID_HTMLDocumentEvents2, NULL);
}

static void destroy_htmldoc(HTMLDocument *This)
{
    remove_target_tasks(This->task_magic);

    ConnectionPointContainer_Destroy(&This->cp_container);
}

static inline HTMLDocumentNode *impl_from_HTMLDOMNode(HTMLDOMNode *iface)
{
    return CONTAINING_RECORD(iface, HTMLDocumentNode, node);
}

static HRESULT HTMLDocumentNode_QI(HTMLDOMNode *iface, REFIID riid, void **ppv)
{
    HTMLDocumentNode *This = impl_from_HTMLDOMNode(iface);

    if(htmldoc_qi(&This->basedoc, riid, ppv))
        return *ppv ? S_OK : E_NOINTERFACE;

    if(IsEqualGUID(&IID_IInternetHostSecurityManager, riid)) {
        TRACE("(%p)->(IID_IInternetHostSecurityManager %p)\n", This, ppv);
        *ppv = &This->IInternetHostSecurityManager_iface;
    }else {
        return HTMLDOMNode_QI(&This->node, riid, ppv);
    }

    IUnknown_AddRef((IUnknown*)*ppv);
    return S_OK;
}

static void HTMLDocumentNode_destructor(HTMLDOMNode *iface)
{
    HTMLDocumentNode *This = impl_from_HTMLDOMNode(iface);

    if(This->body_event_target)
        release_event_target(This->body_event_target);
    if(This->nsevent_listener)
        release_nsevents(This);
    if(This->catmgr)
        ICatInformation_Release(This->catmgr);

    detach_selection(This);
    detach_ranges(This);
    release_nodes(This);

    while(!list_empty(&This->plugin_hosts))
        detach_plugin_host(LIST_ENTRY(list_head(&This->plugin_hosts), PluginHost, entry));

    if(This->nsdoc) {
        release_document_mutation(This);
        nsIDOMHTMLDocument_Release(This->nsdoc);
    }

    heap_free(This->event_vector);
    destroy_htmldoc(&This->basedoc);
}

static HRESULT HTMLDocumentNode_clone(HTMLDOMNode *iface, nsIDOMNode *nsnode, HTMLDOMNode **ret)
{
    HTMLDocumentNode *This = impl_from_HTMLDOMNode(iface);
    FIXME("%p\n", This);
    return E_NOTIMPL;
}

static const NodeImplVtbl HTMLDocumentNodeImplVtbl = {
    HTMLDocumentNode_QI,
    HTMLDocumentNode_destructor,
    HTMLDocumentNode_clone
};

static HRESULT HTMLDocumentFragment_clone(HTMLDOMNode *iface, nsIDOMNode *nsnode, HTMLDOMNode **ret)
{
    HTMLDocumentNode *This = impl_from_HTMLDOMNode(iface);
    HTMLDocumentNode *new_node;
    HRESULT hres;

    hres = create_document_fragment(nsnode, This->node.doc, &new_node);
    if(FAILED(hres))
        return hres;

    *ret = &new_node->node;
    return S_OK;
}

static const NodeImplVtbl HTMLDocumentFragmentImplVtbl = {
    HTMLDocumentNode_QI,
    HTMLDocumentNode_destructor,
    HTMLDocumentFragment_clone
};

static const tid_t HTMLDocumentNode_iface_tids[] = {
    IHTMLDOMNode_tid,
    IHTMLDOMNode2_tid,
    IHTMLDocument2_tid,
    IHTMLDocument3_tid,
    IHTMLDocument4_tid,
    IHTMLDocument5_tid,
    0
};

static dispex_static_data_t HTMLDocumentNode_dispex = {
    NULL,
    DispHTMLDocument_tid,
    NULL,
    HTMLDocumentNode_iface_tids
};

static HTMLDocumentNode *alloc_doc_node(HTMLDocumentObj *doc_obj, HTMLWindow *window)
{
    HTMLDocumentNode *doc;

    doc = heap_alloc_zero(sizeof(HTMLDocumentNode));
    if(!doc)
        return NULL;

    doc->ref = 1;
    doc->basedoc.doc_node = doc;
    doc->basedoc.doc_obj = doc_obj;
    doc->basedoc.window = window;

    init_dispex(&doc->node.dispex, (IUnknown*)&doc->node.IHTMLDOMNode_iface,
            &HTMLDocumentNode_dispex);
    init_doc(&doc->basedoc, (IUnknown*)&doc->node.IHTMLDOMNode_iface,
            &doc->node.dispex.IDispatchEx_iface);
    HTMLDocumentNode_SecMgr_Init(doc);

    init_nsevents(doc);

    list_init(&doc->bindings);
    list_init(&doc->selection_list);
    list_init(&doc->range_list);
    list_init(&doc->plugin_hosts);

    return doc;
}

HRESULT create_doc_from_nsdoc(nsIDOMHTMLDocument *nsdoc, HTMLDocumentObj *doc_obj, HTMLWindow *window, HTMLDocumentNode **ret)
{
    HTMLDocumentNode *doc;

    doc = alloc_doc_node(doc_obj, window);
    if(!doc)
        return E_OUTOFMEMORY;

    if(!doc_obj->basedoc.window || window == doc_obj->basedoc.window)
        doc->basedoc.cp_container.forward_container = &doc_obj->basedoc.cp_container;

    nsIDOMHTMLDocument_AddRef(nsdoc);
    doc->nsdoc = nsdoc;
    init_document_mutation(doc);

    HTMLDOMNode_Init(doc, &doc->node, (nsIDOMNode*)nsdoc);
    doc->node.vtbl = &HTMLDocumentNodeImplVtbl;
    doc->node.cp_container = &doc->basedoc.cp_container;

    *ret = doc;
    return S_OK;
}

HRESULT create_document_fragment(nsIDOMNode *nsnode, HTMLDocumentNode *doc_node, HTMLDocumentNode **ret)
{
    HTMLDocumentNode *doc_frag;

    doc_frag = alloc_doc_node(doc_node->basedoc.doc_obj, doc_node->basedoc.window);
    if(!doc_frag)
        return E_OUTOFMEMORY;

    HTMLDOMNode_Init(doc_node, &doc_frag->node, nsnode);
    doc_frag->node.vtbl = &HTMLDocumentFragmentImplVtbl;
    doc_frag->node.cp_container = &doc_frag->basedoc.cp_container;

    htmldoc_addref(&doc_frag->basedoc);
    *ret = doc_frag;
    return S_OK;
}

/**********************************************************
 * ICustomDoc implementation
 */

static inline HTMLDocumentObj *impl_from_ICustomDoc(ICustomDoc *iface)
{
    return CONTAINING_RECORD(iface, HTMLDocumentObj, ICustomDoc_iface);
}

static HRESULT WINAPI CustomDoc_QueryInterface(ICustomDoc *iface, REFIID riid, void **ppv)
{
    HTMLDocumentObj *This = impl_from_ICustomDoc(iface);

    if(htmldoc_qi(&This->basedoc, riid, ppv))
        return *ppv ? S_OK : E_NOINTERFACE;

    if(IsEqualGUID(&IID_ICustomDoc, riid)) {
        TRACE("(%p)->(IID_ICustomDoc %p)\n", This, ppv);
        *ppv = &This->ICustomDoc_iface;
    }else if(dispex_query_interface(&This->dispex, riid, ppv)) {
        return *ppv ? S_OK : E_NOINTERFACE;
    }else {
        FIXME("Unimplemented interface %s\n", debugstr_guid(riid));
        *ppv = NULL;
        return E_NOINTERFACE;
    }

    IUnknown_AddRef((IUnknown*)*ppv);
    return S_OK;
}

static ULONG WINAPI CustomDoc_AddRef(ICustomDoc *iface)
{
    HTMLDocumentObj *This = impl_from_ICustomDoc(iface);
    ULONG ref = InterlockedIncrement(&This->ref);

    TRACE("(%p) ref = %u\n", This, ref);

    return ref;
}

static ULONG WINAPI CustomDoc_Release(ICustomDoc *iface)
{
    HTMLDocumentObj *This = impl_from_ICustomDoc(iface);
    ULONG ref = InterlockedDecrement(&This->ref);

    TRACE("(%p) ref = %u\n", This, ref);

    if(!ref) {
        if(This->basedoc.doc_node) {
            This->basedoc.doc_node->basedoc.doc_obj = NULL;
            htmldoc_release(&This->basedoc.doc_node->basedoc);
        }
        if(This->basedoc.window) {
            This->basedoc.window->doc_obj = NULL;
            IHTMLWindow2_Release(&This->basedoc.window->IHTMLWindow2_iface);
        }
        if(This->basedoc.advise_holder)
            IOleAdviseHolder_Release(This->basedoc.advise_holder);

        if(This->view_sink)
            IAdviseSink_Release(This->view_sink);
        if(This->client)
            IOleObject_SetClientSite(&This->basedoc.IOleObject_iface, NULL);
        if(This->hostui)
            ICustomDoc_SetUIHandler(&This->ICustomDoc_iface, NULL);
        if(This->in_place_active)
            IOleInPlaceObjectWindowless_InPlaceDeactivate(&This->basedoc.IOleInPlaceObjectWindowless_iface);
        if(This->ipsite)
            IOleDocumentView_SetInPlaceSite(&This->basedoc.IOleDocumentView_iface, NULL);
        if(This->undomgr)
            IOleUndoManager_Release(This->undomgr);
        if(This->tooltips_hwnd)
            DestroyWindow(This->tooltips_hwnd);

        if(This->hwnd)
            DestroyWindow(This->hwnd);
        heap_free(This->mime);

        destroy_htmldoc(&This->basedoc);
        release_dispex(&This->dispex);

        if(This->nscontainer)
            NSContainer_Release(This->nscontainer);
        heap_free(This);
    }

    return ref;
}

static HRESULT WINAPI CustomDoc_SetUIHandler(ICustomDoc *iface, IDocHostUIHandler *pUIHandler)
{
    HTMLDocumentObj *This = impl_from_ICustomDoc(iface);
    IOleCommandTarget *cmdtrg;
    HRESULT hres;

    TRACE("(%p)->(%p)\n", This, pUIHandler);

    if(This->custom_hostui && This->hostui == pUIHandler)
        return S_OK;

    This->custom_hostui = TRUE;

    if(This->hostui)
        IDocHostUIHandler_Release(This->hostui);
    if(pUIHandler)
        IDocHostUIHandler_AddRef(pUIHandler);
    This->hostui = pUIHandler;
    if(!pUIHandler)
        return S_OK;

    hres = IDocHostUIHandler_QueryInterface(pUIHandler, &IID_IOleCommandTarget, (void**)&cmdtrg);
    if(SUCCEEDED(hres)) {
        FIXME("custom UI handler supports IOleCommandTarget\n");
        IOleCommandTarget_Release(cmdtrg);
    }

    return S_OK;
}

static const ICustomDocVtbl CustomDocVtbl = {
    CustomDoc_QueryInterface,
    CustomDoc_AddRef,
    CustomDoc_Release,
    CustomDoc_SetUIHandler
};

static const tid_t HTMLDocumentObj_iface_tids[] = {
    IHTMLDocument2_tid,
    IHTMLDocument3_tid,
    IHTMLDocument4_tid,
    IHTMLDocument5_tid,
    0
};
static dispex_static_data_t HTMLDocumentObj_dispex = {
    NULL,
    DispHTMLDocument_tid,
    NULL,
    HTMLDocumentObj_iface_tids
};

HRESULT HTMLDocument_Create(IUnknown *pUnkOuter, REFIID riid, void** ppvObject)
{
    HTMLDocumentObj *doc;
    nsIDOMWindow *nswindow = NULL;
    nsresult nsres;
    HRESULT hres;

    TRACE("(%p %s %p)\n", pUnkOuter, debugstr_guid(riid), ppvObject);

    doc = heap_alloc_zero(sizeof(HTMLDocumentObj));
    if(!doc)
        return E_OUTOFMEMORY;

    init_dispex(&doc->dispex, (IUnknown*)&doc->ICustomDoc_iface, &HTMLDocumentObj_dispex);
    init_doc(&doc->basedoc, (IUnknown*)&doc->ICustomDoc_iface, &doc->dispex.IDispatchEx_iface);

    doc->ICustomDoc_iface.lpVtbl = &CustomDocVtbl;
    doc->ref = 1;
    doc->basedoc.doc_obj = doc;

    doc->usermode = UNKNOWN_USERMODE;

    doc->nscontainer = NSContainer_Create(doc, NULL);
    if(!doc->nscontainer) {
        ERR("Failed to init Gecko, returning CLASS_E_CLASSNOTAVAILABLE\n");
        htmldoc_release(&doc->basedoc);
        return CLASS_E_CLASSNOTAVAILABLE;
    }

    hres = htmldoc_query_interface(&doc->basedoc, riid, ppvObject);
    htmldoc_release(&doc->basedoc);
    if(FAILED(hres))
        return hres;


    nsres = nsIWebBrowser_GetContentDOMWindow(doc->nscontainer->webbrowser, &nswindow);
    if(NS_FAILED(nsres))
        ERR("GetContentDOMWindow failed: %08x\n", nsres);

    hres = HTMLWindow_Create(doc, nswindow, NULL /* FIXME */, &doc->basedoc.window);
    if(nswindow)
        nsIDOMWindow_Release(nswindow);
    if(FAILED(hres)) {
        htmldoc_release(&doc->basedoc);
        return hres;
    }

    if(!doc->basedoc.doc_node && doc->basedoc.window->doc) {
        doc->basedoc.doc_node = doc->basedoc.window->doc;
        htmldoc_addref(&doc->basedoc.doc_node->basedoc);
    }

    get_thread_hwnd();

    return S_OK;
}
