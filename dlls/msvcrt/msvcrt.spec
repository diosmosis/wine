# msvcrt.dll - MS VC++ Run Time Library

@ cdecl -norelay $I10_OUTPUT(double long long long ptr) MSVCRT_I10_OUTPUT
@ thiscall -arch=win32 ??0__non_rtti_object@@QAE@ABV0@@Z(ptr ptr) MSVCRT___non_rtti_object_copy_ctor
@ cdecl -arch=win64 ??0__non_rtti_object@@QEAA@AEBV0@@Z(ptr ptr) MSVCRT___non_rtti_object_copy_ctor
@ thiscall -arch=win32 ??0__non_rtti_object@@QAE@PBD@Z(ptr ptr) MSVCRT___non_rtti_object_ctor
@ cdecl -arch=win64 ??0__non_rtti_object@@QEAA@PEBD@Z(ptr ptr) MSVCRT___non_rtti_object_ctor
@ thiscall -arch=win32 ??0bad_cast@@AAE@PBQBD@Z(ptr ptr) MSVCRT_bad_cast_ctor
@ cdecl -arch=win64 ??0bad_cast@@AEAA@PEBQEBD@Z(ptr ptr) MSVCRT_bad_cast_ctor
@ thiscall -arch=win32 ??0bad_cast@@QAE@ABQBD@Z(ptr ptr) MSVCRT_bad_cast_ctor
@ cdecl -arch=win64 ??0bad_cast@@QEAA@AEBQEBD@Z(ptr ptr) MSVCRT_bad_cast_ctor
@ thiscall -arch=win32 ??0bad_cast@@QAE@ABV0@@Z(ptr ptr) MSVCRT_bad_cast_copy_ctor
@ cdecl -arch=win64 ??0bad_cast@@QEAA@AEBV0@@Z(ptr ptr) MSVCRT_bad_cast_copy_ctor
@ thiscall -arch=win32 ??0bad_cast@@QAE@PBD@Z(ptr str) MSVCRT_bad_cast_ctor_charptr
@ cdecl -arch=win64 ??0bad_cast@@QEAA@PEBD@Z(ptr str) MSVCRT_bad_cast_ctor_charptr
@ thiscall -arch=win32 ??0bad_typeid@@QAE@ABV0@@Z(ptr ptr) MSVCRT_bad_typeid_copy_ctor
@ cdecl -arch=win64 ??0bad_typeid@@QEAA@AEBV0@@Z(ptr ptr) MSVCRT_bad_typeid_copy_ctor
@ thiscall -arch=win32 ??0bad_typeid@@QAE@PBD@Z(ptr str) MSVCRT_bad_typeid_ctor
@ cdecl -arch=win64 ??0bad_typeid@@QEAA@PEBD@Z(ptr str) MSVCRT_bad_typeid_ctor
@ thiscall -arch=win32 ??0exception@@QAE@ABQBD@Z(ptr ptr) MSVCRT_exception_ctor
@ cdecl -arch=win64 ??0exception@@QEAA@AEBQEBD@Z(ptr ptr) MSVCRT_exception_ctor
@ thiscall -arch=win32 ??0exception@@QAE@ABQBDH@Z(ptr ptr long) MSVCRT_exception_ctor_noalloc
@ cdecl -arch=win64 ??0exception@@QEAA@AEBQEBDH@Z(ptr ptr long) MSVCRT_exception_ctor_noalloc
@ thiscall -arch=win32 ??0exception@@QAE@ABV0@@Z(ptr ptr) MSVCRT_exception_copy_ctor
@ cdecl -arch=win64 ??0exception@@QEAA@AEBV0@@Z(ptr ptr) MSVCRT_exception_copy_ctor
@ thiscall -arch=win32 ??0exception@@QAE@XZ(ptr) MSVCRT_exception_default_ctor
@ cdecl -arch=win64 ??0exception@@QEAA@XZ(ptr) MSVCRT_exception_default_ctor
@ thiscall -arch=win32 ??1__non_rtti_object@@UAE@XZ(ptr) MSVCRT___non_rtti_object_dtor
@ cdecl -arch=win64 ??1__non_rtti_object@@UEAA@XZ(ptr) MSVCRT___non_rtti_object_dtor
@ thiscall -arch=win32 ??1bad_cast@@UAE@XZ(ptr) MSVCRT_bad_cast_dtor
@ cdecl -arch=win64 ??1bad_cast@@UEAA@XZ(ptr) MSVCRT_bad_cast_dtor
@ thiscall -arch=win32 ??1bad_typeid@@UAE@XZ(ptr) MSVCRT_bad_typeid_dtor
@ cdecl -arch=win64 ??1bad_typeid@@UEAA@XZ(ptr) MSVCRT_bad_typeid_dtor
@ thiscall -arch=win32 ??1exception@@UAE@XZ(ptr) MSVCRT_exception_dtor
@ cdecl -arch=win64 ??1exception@@UEAA@XZ(ptr) MSVCRT_exception_dtor
@ thiscall -arch=win32 ??1type_info@@UAE@XZ(ptr) MSVCRT_type_info_dtor
@ cdecl -arch=win64 ??1type_info@@UEAA@XZ(ptr) MSVCRT_type_info_dtor
@ cdecl -arch=win32 ??2@YAPAXI@Z(long) MSVCRT_operator_new
@ cdecl -arch=win64 ??2@YAPEAX_K@Z(long) MSVCRT_operator_new
@ cdecl -arch=win32 ??2@YAPAXIHPBDH@Z(long long str long) MSVCRT_operator_new_dbg
@ cdecl -arch=win64 ??2@YAPEAX_KHPEBDH@Z(long long str long) MSVCRT_operator_new_dbg
@ cdecl -arch=win32 ??3@YAXPAX@Z(ptr) MSVCRT_operator_delete
@ cdecl -arch=win64 ??3@YAXPEAX@Z(ptr) MSVCRT_operator_delete
@ thiscall -arch=win32 ??4__non_rtti_object@@QAEAAV0@ABV0@@Z(ptr ptr) MSVCRT___non_rtti_object_opequals
@ cdecl -arch=win64 ??4__non_rtti_object@@QEAAAEAV0@AEBV0@@Z(ptr ptr) MSVCRT___non_rtti_object_opequals
@ thiscall -arch=win32 ??4bad_cast@@QAEAAV0@ABV0@@Z(ptr ptr) MSVCRT_bad_cast_opequals
@ cdecl -arch=win64 ??4bad_cast@@QEAAAEAV0@AEBV0@@Z(ptr ptr) MSVCRT_bad_cast_opequals
@ thiscall -arch=win32 ??4bad_typeid@@QAEAAV0@ABV0@@Z(ptr ptr) MSVCRT_bad_typeid_opequals
@ cdecl -arch=win64 ??4bad_typeid@@QEAAAEAV0@AEBV0@@Z(ptr ptr) MSVCRT_bad_typeid_opequals
@ thiscall -arch=win32 ??4exception@@QAEAAV0@ABV0@@Z(ptr ptr) MSVCRT_exception_opequals
@ cdecl -arch=win64 ??4exception@@QEAAAEAV0@AEBV0@@Z(ptr ptr) MSVCRT_exception_opequals
@ thiscall -arch=win32 ??8type_info@@QBEHABV0@@Z(ptr ptr) MSVCRT_type_info_opequals_equals
@ cdecl -arch=win64 ??8type_info@@QEBAHAEBV0@@Z(ptr ptr) MSVCRT_type_info_opequals_equals
@ thiscall -arch=win32 ??9type_info@@QBEHABV0@@Z(ptr ptr) MSVCRT_type_info_opnot_equals
@ cdecl -arch=win64 ??9type_info@@QEBAHAEBV0@@Z(ptr ptr) MSVCRT_type_info_opnot_equals
@ extern ??_7__non_rtti_object@@6B@ MSVCRT___non_rtti_object_vtable
@ extern ??_7bad_cast@@6B@ MSVCRT_bad_cast_vtable
@ extern ??_7bad_typeid@@6B@ MSVCRT_bad_typeid_vtable
@ extern ??_7exception@@6B@ MSVCRT_exception_vtable
@ thiscall -arch=win32 ??_E__non_rtti_object@@UAEPAXI@Z(ptr long) MSVCRT___non_rtti_object_vector_dtor
@ thiscall -arch=win32 ??_Ebad_cast@@UAEPAXI@Z(ptr long) MSVCRT_bad_cast_vector_dtor
@ thiscall -arch=win32 ??_Ebad_typeid@@UAEPAXI@Z(ptr long) MSVCRT_bad_typeid_vector_dtor
@ thiscall -arch=win32 ??_Eexception@@UAEPAXI@Z(ptr long) MSVCRT_exception_vector_dtor
@ thiscall -arch=win32 ??_Fbad_cast@@QAEXXZ(ptr) MSVCRT_bad_cast_default_ctor
@ cdecl -arch=win64 ??_Fbad_cast@@QEAAXXZ(ptr) MSVCRT_bad_cast_default_ctor
@ thiscall -arch=win32 ??_Fbad_typeid@@QAEXXZ(ptr) MSVCRT_bad_typeid_default_ctor
@ cdecl -arch=win64 ??_Fbad_typeid@@QEAAXXZ(ptr) MSVCRT_bad_typeid_default_ctor
@ thiscall -arch=win32 ??_G__non_rtti_object@@UAEPAXI@Z(ptr long) MSVCRT___non_rtti_object_scalar_dtor
@ thiscall -arch=win32 ??_Gbad_cast@@UAEPAXI@Z(ptr long) MSVCRT_bad_cast_scalar_dtor
@ thiscall -arch=win32 ??_Gbad_typeid@@UAEPAXI@Z(ptr long) MSVCRT_bad_typeid_scalar_dtor
@ thiscall -arch=win32 ??_Gexception@@UAEPAXI@Z(ptr long) MSVCRT_exception_scalar_dtor
@ cdecl -arch=win32 ??_U@YAPAXI@Z(long) MSVCRT_operator_new
@ cdecl -arch=win64 ??_U@YAPEAX_K@Z(long) MSVCRT_operator_new
@ cdecl -arch=win32 ??_U@YAPAXIHPBDH@Z(long long str long) MSVCRT_operator_new_dbg
@ cdecl -arch=win64 ??_U@YAPEAX_KHPEBDH@Z(long long str long) MSVCRT_operator_new_dbg
@ cdecl -arch=win32 ??_V@YAXPAX@Z(ptr) MSVCRT_operator_delete
@ cdecl -arch=win64 ??_V@YAXPEAX@Z(ptr) MSVCRT_operator_delete
@ cdecl -arch=win32 ?_query_new_handler@@YAP6AHI@ZXZ() MSVCRT__query_new_handler
@ cdecl -arch=win64 ?_query_new_handler@@YAP6AH_K@ZXZ() MSVCRT__query_new_handler
@ cdecl ?_query_new_mode@@YAHXZ() MSVCRT__query_new_mode
@ cdecl -arch=win32 ?_set_new_handler@@YAP6AHI@ZP6AHI@Z@Z(ptr) MSVCRT__set_new_handler
@ cdecl -arch=win64 ?_set_new_handler@@YAP6AH_K@ZP6AH0@Z@Z(ptr) MSVCRT__set_new_handler
@ cdecl ?_set_new_mode@@YAHH@Z(long) MSVCRT__set_new_mode
@ cdecl -arch=win32 ?_set_se_translator@@YAP6AXIPAU_EXCEPTION_POINTERS@@@ZP6AXI0@Z@Z(ptr) MSVCRT__set_se_translator
@ cdecl -arch=win64 ?_set_se_translator@@YAP6AXIPEAU_EXCEPTION_POINTERS@@@ZP6AXI0@Z@Z(ptr) MSVCRT__set_se_translator
@ thiscall -arch=win32 ?before@type_info@@QBEHABV1@@Z(ptr ptr) MSVCRT_type_info_before
@ cdecl -arch=win64 ?before@type_info@@QEBAHAEBV1@@Z(ptr ptr) MSVCRT_type_info_before
@ thiscall -arch=win32 ?name@type_info@@QBEPBDXZ(ptr) MSVCRT_type_info_name
@ cdecl -arch=win64 ?name@type_info@@QEBAPEBDXZ(ptr) MSVCRT_type_info_name
@ thiscall -arch=win32 ?raw_name@type_info@@QBEPBDXZ(ptr) MSVCRT_type_info_raw_name
@ cdecl -arch=win64 ?raw_name@type_info@@QEBAPEBDXZ(ptr) MSVCRT_type_info_raw_name
@ cdecl ?set_new_handler@@YAP6AXXZP6AXXZ@Z(ptr) MSVCRT_set_new_handler
@ cdecl ?set_terminate@@YAP6AXXZP6AXXZ@Z(ptr) MSVCRT_set_terminate
@ cdecl ?set_unexpected@@YAP6AXXZP6AXXZ@Z(ptr) MSVCRT_set_unexpected
@ cdecl ?terminate@@YAXXZ() MSVCRT_terminate
@ cdecl ?unexpected@@YAXXZ() MSVCRT_unexpected
@ thiscall -arch=win32 ?what@exception@@UBEPBDXZ(ptr) MSVCRT_what_exception
@ cdecl -arch=win64 ?what@exception@@UEBAPEBDXZ(ptr) MSVCRT_what_exception
@ cdecl -arch=i386 _CIacos()
@ cdecl -arch=i386 _CIasin()
@ cdecl -arch=i386 _CIatan()
@ cdecl -arch=i386 _CIatan2()
@ cdecl -arch=i386 _CIcos()
@ cdecl -arch=i386 _CIcosh()
@ cdecl -arch=i386 _CIexp()
@ cdecl -arch=i386 _CIfmod()
@ cdecl -arch=i386 _CIlog()
@ cdecl -arch=i386 _CIlog10()
@ cdecl -arch=i386 _CIpow()
@ cdecl -arch=i386 _CIsin()
@ cdecl -arch=i386 _CIsinh()
@ cdecl -arch=i386 _CIsqrt()
@ cdecl -arch=i386 _CItan()
@ cdecl -arch=i386 _CItanh()
# stub _CrtCheckMemory
# stub _CrtDbgBreak
# stub _CrtDbgReport
# stub _CrtDbgReportV
# stub _CrtDbgReportW
# stub _CrtDbgReportWV
# stub _CrtDoForAllClientObjects
# stub _CrtDumpMemoryLeaks
# stub _CrtIsMemoryBlock
# stub _CrtIsValidHeapPointer
# stub _CrtIsValidPointer
# stub _CrtMemCheckpoint
# stub _CrtMemDifference
# stub _CrtMemDumpAllObjectsSince
# stub _CrtMemDumpStatistics
# stub _CrtReportBlockType
# stub _CrtSetAllocHook
# stub _CrtSetBreakAlloc
# stub _CrtSetDbgBlockType
# stub _CrtSetDbgFlag
# stub _CrtSetDumpClient
# stub _CrtSetReportFile
# stub _CrtSetReportHook
# stub _CrtSetReportHook2
# stub _CrtSetReportMode
@ stdcall _CxxThrowException(long long)
@ cdecl -i386 -norelay _EH_prolog()
@ cdecl _Getdays()
@ cdecl _Getmonths()
@ cdecl _Gettnames()
@ extern _HUGE MSVCRT__HUGE
@ cdecl _Strftime(str long str ptr ptr)
@ cdecl _XcptFilter(long ptr)
@ cdecl __CppXcptFilter(long ptr)
# stub __CxxCallUnwindDelDtor
# stub __CxxCallUnwindDtor
# stub __CxxCallUnwindVecDtor
@ cdecl __CxxDetectRethrow(ptr)
# stub __CxxExceptionFilter
@ cdecl -i386 -norelay __CxxFrameHandler(ptr ptr ptr ptr)
@ cdecl -i386 -norelay __CxxFrameHandler2(ptr ptr ptr ptr) __CxxFrameHandler
@ cdecl -i386 -norelay __CxxFrameHandler3(ptr ptr ptr ptr) __CxxFrameHandler
@ stdcall -arch=x86_64 __C_specific_handler(ptr long ptr ptr) ntdll.__C_specific_handler
@ stdcall -i386 __CxxLongjmpUnwind(ptr)
@ cdecl __CxxQueryExceptionSize()
# stub __CxxRegisterExceptionObject
# stub __CxxUnregisterExceptionObject
# stub __DestructExceptionObject
@ cdecl __RTCastToVoid(ptr) MSVCRT___RTCastToVoid
@ cdecl __RTDynamicCast(ptr long ptr ptr long) MSVCRT___RTDynamicCast
@ cdecl __RTtypeid(ptr) MSVCRT___RTtypeid
@ cdecl __STRINGTOLD(ptr ptr str long)
@ cdecl ___lc_codepage_func()
@ cdecl ___lc_collate_cp_func()
@ cdecl ___lc_handle_func()
@ cdecl ___mb_cur_max_func() MSVCRT____mb_cur_max_func
@ cdecl ___setlc_active_func() MSVCRT____setlc_active_func
@ cdecl ___unguarded_readlc_active_add_func() MSVCRT____unguarded_readlc_active_add_func
@ extern __argc MSVCRT___argc
@ extern __argv MSVCRT___argv
@ extern __badioinfo MSVCRT___badioinfo
@ cdecl __crtCompareStringA(long long str long str long)
@ cdecl __crtCompareStringW(long long wstr long wstr long)
@ cdecl __crtGetLocaleInfoW(long long ptr long)
@ cdecl __crtGetStringTypeW(long long wstr long ptr)
@ cdecl __crtLCMapStringA(long long str long ptr long long long)
@ cdecl __crtLCMapStringW(long long wstr long ptr long long long)
@ cdecl __daylight() MSVCRT___p__daylight
@ cdecl __dllonexit(ptr ptr ptr)
@ cdecl __doserrno() MSVCRT___doserrno
# stub __dstbias()
@ cdecl __fpecode()
@ stub __get_app_type
@ cdecl __getmainargs(ptr ptr ptr long ptr)
@ extern __initenv MSVCRT___initenv
@ cdecl __iob_func() MSVCRT___iob_func
@ cdecl __isascii(long) MSVCRT___isascii
@ cdecl __iscsym(long) MSVCRT___iscsym
@ cdecl __iscsymf(long) MSVCRT___iscsymf
@ extern __lc_codepage MSVCRT___lc_codepage
@ stub __lc_collate
@ extern __lc_collate_cp MSVCRT___lc_collate_cp
@ extern __lc_handle MSVCRT___lc_handle
@ cdecl __lconv_init()
@ cdecl -arch=i386 __libm_sse2_acos()
@ cdecl -arch=i386 __libm_sse2_acosf()
@ cdecl -arch=i386 __libm_sse2_asin()
@ cdecl -arch=i386 __libm_sse2_asinf()
@ cdecl -arch=i386 __libm_sse2_atan()
@ cdecl -arch=i386 __libm_sse2_atan2()
@ cdecl -arch=i386 __libm_sse2_atanf()
@ cdecl -arch=i386 __libm_sse2_cos()
@ cdecl -arch=i386 __libm_sse2_cosf()
@ cdecl -arch=i386 __libm_sse2_exp()
@ cdecl -arch=i386 __libm_sse2_expf()
@ cdecl -arch=i386 __libm_sse2_log()
@ cdecl -arch=i386 __libm_sse2_log10()
@ cdecl -arch=i386 __libm_sse2_log10f()
@ cdecl -arch=i386 __libm_sse2_logf()
@ cdecl -arch=i386 __libm_sse2_pow()
@ cdecl -arch=i386 __libm_sse2_powf()
@ cdecl -arch=i386 __libm_sse2_sin()
@ cdecl -arch=i386 __libm_sse2_sinf()
@ cdecl -arch=i386 __libm_sse2_tan()
@ cdecl -arch=i386 __libm_sse2_tanf()
@ extern __mb_cur_max MSVCRT___mb_cur_max
@ cdecl __p___argc()
@ cdecl __p___argv()
@ cdecl __p___initenv()
@ cdecl __p___mb_cur_max() MSVCRT____mb_cur_max_func
@ cdecl __p___wargv()
@ cdecl __p___winitenv()
@ cdecl __p__acmdln()
@ cdecl __p__amblksiz()
@ cdecl __p__commode()
@ cdecl __p__daylight() MSVCRT___p__daylight
@ cdecl __p__dstbias()
@ cdecl __p__environ()
@ stub __p__fileinfo()
@ cdecl __p__fmode()
@ cdecl __p__iob() MSVCRT___iob_func
@ stub __p__mbcasemap()
@ cdecl __p__mbctype()
@ cdecl __p__osver()
@ cdecl __p__pctype() MSVCRT___pctype_func
@ cdecl __p__pgmptr()
@ stub __p__pwctype()
@ cdecl __p__timezone() MSVCRT___p__timezone
@ cdecl __p__tzname()
@ cdecl __p__wcmdln()
@ cdecl __p__wenviron()
@ cdecl __p__winmajor()
@ cdecl __p__winminor()
@ cdecl __p__winver()
@ cdecl __p__wpgmptr()
@ cdecl __pctype_func() MSVCRT___pctype_func
@ extern __pioinfo MSVCRT___pioinfo
# stub __pwctype_func()
@ stub __pxcptinfoptrs()
@ cdecl __set_app_type(long) MSVCRT___set_app_type
@ extern __setlc_active MSVCRT___setlc_active
@ cdecl __setusermatherr(ptr) MSVCRT___setusermatherr
# stub __strncnt(str long)
@ cdecl __threadhandle() kernel32.GetCurrentThread
@ cdecl __threadid() kernel32.GetCurrentThreadId
@ cdecl __toascii(long) MSVCRT___toascii
@ cdecl __uncaught_exception() MSVCRT___uncaught_exception
@ cdecl __unDName(ptr str long ptr ptr long)
@ cdecl __unDNameEx(ptr str long ptr ptr ptr long)
@ extern __unguarded_readlc_active MSVCRT___unguarded_readlc_active
@ extern __wargv MSVCRT___wargv
@ cdecl __wcserror(wstr)
@ cdecl __wcserror_s(ptr long wstr)
# stub __wcsncnt(wstr long)
@ cdecl __wgetmainargs(ptr ptr ptr long ptr)
@ extern __winitenv MSVCRT___winitenv
@ cdecl _abnormal_termination()
@ cdecl -ret64 _abs64(int64)
@ cdecl _access(str long) MSVCRT__access
@ cdecl _access_s(str long)
@ extern _acmdln MSVCRT__acmdln
@ stdcall -arch=i386 _adj_fdiv_m16i(long)
@ stdcall -arch=i386 _adj_fdiv_m32(long)
@ stdcall -arch=i386 _adj_fdiv_m32i(long)
@ stdcall -arch=i386 _adj_fdiv_m64(int64)
@ cdecl -arch=i386 _adj_fdiv_r()
@ stdcall -arch=i386 _adj_fdivr_m16i(long)
@ stdcall -arch=i386 _adj_fdivr_m32(long)
@ stdcall -arch=i386 _adj_fdivr_m32i(long)
@ stdcall -arch=i386 _adj_fdivr_m64(int64)
@ cdecl -arch=i386 _adj_fpatan()
@ cdecl -arch=i386 _adj_fprem()
@ cdecl -arch=i386 _adj_fprem1()
@ cdecl -arch=i386 _adj_fptan()
@ extern -arch=i386 _adjust_fdiv MSVCRT__adjust_fdiv
@ extern _aexit_rtn
@ cdecl _aligned_free(ptr)
# stub _aligned_free_dbg(ptr)
@ cdecl _aligned_malloc(long long)
# stub _aligned_malloc_dbg(long long str long)
@ cdecl _aligned_offset_malloc(long long long)
# stub _aligned_offset_malloc_dbg(long long long str long)
@ cdecl _aligned_offset_realloc(ptr long long long)
# stub _aligned_offset_realloc_dbg(ptr long long long str long)
@ cdecl _aligned_realloc(ptr long long)
# stub _aligned_realloc_dbg(ptr long long str long)
@ cdecl _amsg_exit(long)
@ cdecl _assert(str str long) MSVCRT__assert
@ stub _atodbl(ptr str)
# stub _atodbl_l(ptr str ptr)
@ cdecl _atof_l(str ptr) MSVCRT__atof_l
@ cdecl _atoflt_l(ptr str ptr) MSVCRT__atoflt_l
@ cdecl -ret64 _atoi64(str) ntdll._atoi64
# stub -ret64 _atoi64_l(str ptr)
# stub _atoi_l(str ptr)
# stub _atol_l(str ptr)
@ cdecl _atoldbl(ptr str) MSVCRT__atoldbl
# stub _atoldbl_l(ptr str ptr)
@ cdecl _beep(long long)
@ cdecl _beginthread (ptr long ptr)
@ cdecl _beginthreadex (ptr long ptr ptr long ptr)
@ cdecl _c_exit() MSVCRT__c_exit
@ cdecl _cabs(long) MSVCRT__cabs
@ cdecl _callnewh(long)
# stub _calloc_dbg(long long long str long)
@ cdecl _cexit() MSVCRT__cexit
@ cdecl _cgets(ptr)
# stub _cgets_s(ptr long ptr)
# stub _cgetws(ptr)
# stub _cgetws_s(ptr long ptr)
@ cdecl _chdir(str) MSVCRT__chdir
@ cdecl _chdrive(long)
@ cdecl _chgsign( double )
# stub -arch=win64 _chgsignf(float)
@ cdecl -i386 -norelay _chkesp()
@ cdecl _chmod(str long) MSVCRT__chmod
@ cdecl _chsize(long long) MSVCRT__chsize
# stub _chsize_s(long int64)
# stub _chvalidator(long long)
# stub _chvalidator_l(ptr long long)
@ cdecl _clearfp()
@ cdecl _close(long) MSVCRT__close
@ cdecl _commit(long)
@ extern _commode MSVCRT__commode
@ cdecl _control87(long long)
@ cdecl _controlfp(long long)
@ cdecl _controlfp_s(ptr long long)
@ cdecl _copysign( double double )
# stub -arch=win64 _copysignf(float float)
@ varargs _cprintf(str)
# stub _cprintf_l(str ptr)
# stub _cprintf_p(str)
# stub _cprintf_p_l(str ptr)
# stub _cprintf_s(str)
# stub _cprintf_s_l(str ptr)
@ cdecl _cputs(str)
@ cdecl _cputws(wstr)
@ cdecl _creat(str long) MSVCRT__creat
# stub _crtAssertBusy
# stub _crtBreakAlloc
# stub _crtDbgFlag
@ varargs _cscanf(str)
@ varargs _cscanf_l(str ptr)
@ varargs _cscanf_s(str)
@ varargs _cscanf_s_l(str ptr)
@ cdecl _ctime32(ptr) MSVCRT__ctime32
@ cdecl _ctime32_s(str long ptr) MSVCRT__ctime32_s
@ cdecl _ctime64(ptr) MSVCRT__ctime64
@ cdecl _ctime64_s(str long ptr) MSVCRT__ctime64_s
@ extern _ctype MSVCRT__ctype
@ cdecl _cwait(ptr long long)
@ varargs _cwprintf(wstr)
# stub _cwprintf_l(wstr ptr)
# stub _cwprintf_p(wstr)
# stub _cwprintf_p_l(wstr ptr)
# stub _cwprintf_s(wstr)
# stub _cwprintf_s_l(wstr ptr)
@ varargs _cwscanf(wstr)
@ varargs _cwscanf_l(wstr ptr)
@ varargs _cwscanf_s(wstr)
@ varargs _cwscanf_s_l(wstr ptr)
@ extern _daylight MSVCRT___daylight
@ cdecl _difftime32(long long) MSVCRT__difftime32
@ cdecl _difftime64(long long) MSVCRT__difftime64
@ extern _dstbias MSVCRT__dstbias
@ cdecl _dup (long) MSVCRT__dup
@ cdecl _dup2 (long long) MSVCRT__dup2
@ cdecl _ecvt(double long ptr ptr)
@ cdecl _ecvt_s(str long double long ptr ptr)
@ cdecl _endthread ()
@ cdecl _endthreadex(long)
@ extern _environ MSVCRT__environ
@ cdecl _eof(long)
@ cdecl _errno() MSVCRT__errno
@ cdecl -i386 _except_handler2(ptr ptr ptr ptr)
@ cdecl -i386 _except_handler3(ptr ptr ptr ptr)
@ cdecl -i386 _except_handler4_common(ptr ptr ptr ptr ptr ptr)
@ varargs _execl(str str)
@ varargs _execle(str str)
@ varargs _execlp(str str)
@ varargs _execlpe(str str)
@ cdecl _execv(str ptr)
@ cdecl _execve(str ptr ptr) MSVCRT__execve
@ cdecl _execvp(str ptr)
@ cdecl _execvpe(str ptr ptr)
@ cdecl _exit(long) MSVCRT__exit
@ cdecl _expand(ptr long)
# stub _expand_dbg(ptr long long str long)
@ cdecl _fcloseall() MSVCRT__fcloseall
@ cdecl _fcvt(double long ptr ptr)
@ cdecl _fcvt_s(ptr long double long ptr ptr)
@ cdecl _fdopen(long str) MSVCRT__fdopen
@ cdecl _fgetchar()
@ cdecl _fgetwchar()
@ cdecl _filbuf(ptr) MSVCRT__filbuf
# extern _fileinfo
@ cdecl _filelength(long) MSVCRT__filelength
@ cdecl -ret64 _filelengthi64(long) MSVCRT__filelengthi64
@ cdecl _fileno(ptr) MSVCRT__fileno
@ cdecl _findclose(long) MSVCRT__findclose
@ cdecl _findfirst(str ptr) MSVCRT__findfirst
@ cdecl _findfirst32(str ptr) MSVCRT__findfirst32
@ cdecl _findfirst64(str ptr) MSVCRT__findfirst64
@ cdecl _findfirst64i32(str ptr) MSVCRT__findfirst64i32
@ cdecl _findfirsti64(str ptr) MSVCRT__findfirsti64
@ cdecl _findnext(long ptr) MSVCRT__findnext
@ cdecl _findnext32(long ptr) MSVCRT__findnext32
@ cdecl _findnext64(long ptr) MSVCRT__findnext64
@ cdecl _findnext64i32(long ptr) MSVCRT__findnext64i32
@ cdecl _findnexti64(long ptr) MSVCRT__findnexti64
@ cdecl _finite( double )
# stub -arch=win64 _finitef(float)
@ cdecl _flsbuf(long ptr) MSVCRT__flsbuf
@ cdecl _flushall()
@ extern _fmode MSVCRT__fmode
@ cdecl _fpclass(double)
# stub -arch=win64 _fpclassf(float)
@ stub _fpieee_flt(long ptr ptr)
@ cdecl _fpreset()
# stub _fprintf_l(ptr str ptr)
# stub _fprintf_p(ptr str)
# stub _fprintf_p_l(ptr str ptr)
# stub _fprintf_s_l(ptr str ptr)
@ cdecl _fputchar(long)
@ cdecl _fputwchar(long)
# stub _free_dbg(ptr long)
# stub _freea(ptr)
# stub _freea_s
@ varargs _fscanf_l(ptr str ptr) MSVCRT__fscanf_l
@ varargs _fscanf_s_l(ptr str ptr) MSVCRT__fscanf_s_l
@ cdecl _fseeki64(ptr int64 long) MSVCRT__fseeki64
@ cdecl _fsopen(str str long) MSVCRT__fsopen
@ cdecl _fstat(long ptr) MSVCRT__fstat
@ cdecl _fstat64(long ptr) MSVCRT__fstat64
@ cdecl _fstati64(long ptr) MSVCRT__fstati64
@ cdecl -ret64 _ftelli64(ptr) MSVCRT__ftelli64
@ cdecl _ftime(ptr) MSVCRT__ftime
@ cdecl _ftime32(ptr) MSVCRT__ftime32
@ cdecl _ftime32_s(ptr) MSVCRT__ftime32_s
@ cdecl _ftime64(ptr) MSVCRT__ftime64
@ cdecl _ftime64_s(ptr) MSVCRT__ftime64_s
@ cdecl -ret64 _ftol() ntdll._ftol
@ cdecl -ret64 _ftol2() ntdll._ftol
@ cdecl -ret64 _ftol2_sse() ntdll._ftol #FIXME: SSE variant should be implemented
# stub _ftol2_sse_excpt
@ cdecl _fullpath(ptr str long)
# stub _fullpath_dbg(ptr str long long str long)
@ cdecl _futime(long ptr)
@ cdecl _futime32(long ptr)
@ cdecl _futime64(long ptr)
# stub _fwprintf_l(ptr wstr ptr)
# stub _fwprintf_p(ptr wstr)
# stub _fwprintf_p_l(ptr wstr ptr)
# stub _fwprintf_s_l(ptr wstr ptr)
@ varargs _fwscanf_l(ptr wstr ptr) MSVCRT__fwscanf_l
@ varargs _fwscanf_s_l(ptr wstr ptr) MSVCRT__fwscanf_s_l
@ cdecl _gcvt(double long str)
@ cdecl _gcvt_s(ptr long  double long)
@ cdecl _get_doserrno(ptr)
# stub _get_environ(ptr)
@ cdecl _get_errno(ptr)
# stub _get_fileinfo(ptr)
# stub _get_fmode(ptr)
@ cdecl _get_heap_handle()
@ cdecl _get_osfhandle(long)
@ cdecl _get_osplatform(ptr) MSVCRT__get_osplatform
# stub _get_osver(ptr)
@ cdecl _get_output_format()
# stub _get_pgmptr(ptr)
@ cdecl _get_sbh_threshold()
# stub _get_wenviron(ptr)
# stub _get_winmajor(ptr)
# stub _get_winminor(ptr)
# stub _get_winver(ptr)
# stub _get_wpgmptr(ptr)
@ cdecl _get_terminate() MSVCRT__get_terminate
@ cdecl _get_tzname(ptr str long long) MSVCRT__get_tzname
@ stub _get_unexpected()
@ cdecl _getch()
@ cdecl _getche()
@ cdecl _getcwd(str long)
@ cdecl _getdcwd(long str long)
@ cdecl _getdiskfree(long ptr) MSVCRT__getdiskfree
@ cdecl _getdllprocaddr(long str long)
@ cdecl _getdrive()
@ cdecl _getdrives() kernel32.GetLogicalDrives
@ cdecl _getmaxstdio()
@ cdecl _getmbcp()
@ cdecl _getpid() kernel32.GetCurrentProcessId
@ stub _getsystime(ptr)
@ cdecl _getw(ptr) MSVCRT__getw
# stub _getwch()
# stub _getwche()
@ cdecl _getws(ptr) MSVCRT__getws
@ cdecl -i386 _global_unwind2(ptr)
@ cdecl _gmtime32(ptr) MSVCRT__gmtime32
@ cdecl _gmtime32_s(ptr ptr) MSVCRT__gmtime32_s
@ cdecl _gmtime64(ptr) MSVCRT__gmtime64
@ cdecl _gmtime64_s(ptr ptr) MSVCRT__gmtime64_s
@ cdecl _heapadd (ptr long)
@ cdecl _heapchk()
@ cdecl _heapmin()
@ cdecl _heapset(long)
@ stub _heapused(ptr ptr)
@ cdecl _heapwalk(ptr)
@ cdecl _hypot(double double)
@ cdecl _hypotf(float float)
@ cdecl _i64toa(int64 ptr long) ntdll._i64toa
@ cdecl _i64toa_s(int64 ptr long long) _i64toa_s
@ cdecl _i64tow(int64 ptr long) ntdll._i64tow
@ cdecl _i64tow_s(int64 ptr long long) _i64tow_s
@ cdecl _initterm(ptr ptr)
@ cdecl _initterm_e(ptr ptr)
@ stub -arch=i386 _inp(long)
@ stub -arch=i386 _inpd(long)
@ stub -arch=i386 _inpw(long)
@ cdecl _invalid_parameter(wstr wstr wstr long long) MSVCRT__invalid_parameter
@ extern _iob MSVCRT__iob
@ cdecl _isalnum_l(long ptr) MSVCRT__isalnum_l
@ cdecl _isalpha_l(long ptr) MSVCRT__isalpha_l
@ cdecl _isatty(long)
@ cdecl _iscntrl_l(long ptr) MSVCRT__iscntrl_l
@ cdecl _isctype(long long)
@ cdecl _isctype_l(long long ptr)
@ cdecl _isdigit_l(long ptr) MSVCRT__isdigit_l
@ cdecl _isgraph_l(long ptr) MSVCRT__isgraph_l
@ cdecl _isleadbyte_l(long ptr) MSVCRT__isleadbyte_l
@ cdecl _islower_l(long ptr) MSVCRT__islower_l
@ stub _ismbbalnum(long)
# stub _ismbbalnum_l(long ptr)
@ stub _ismbbalpha(long)
# stub _ismbbalpha_l(long ptr)
@ stub _ismbbgraph(long)
# stub _ismbbgraph_l(long ptr)
@ stub _ismbbkalnum(long)
# stub _ismbbkalnum_l(long ptr)
@ cdecl _ismbbkana(long)
# stub _ismbbkana_l(long ptr)
@ stub _ismbbkprint(long)
# stub _ismbbkprint_l(long ptr)
@ stub _ismbbkpunct(long)
# stub _ismbbkpunct_l(long ptr)
@ cdecl _ismbblead(long)
# stub _ismbblead_l(long ptr)
@ stub _ismbbprint(long)
# stub _ismbbprint_l(long ptr)
@ stub _ismbbpunct(long)
# stub _ismbbpunct_l(long ptr)
@ cdecl _ismbbtrail(long)
# stub _ismbbtrail_l(long ptr)
@ cdecl _ismbcalnum(long)
# stub _ismbcalnum_l(long ptr)
@ cdecl _ismbcalpha(long)
# stub _ismbcalpha_l(long ptr)
@ cdecl _ismbcdigit(long)
# stub _ismbcdigit_l(long ptr)
@ cdecl _ismbcgraph(long)
# stub _ismbcgraph_l(long ptr)
@ cdecl _ismbchira(long)
# stub _ismbchira_l(long ptr)
@ cdecl _ismbckata(long)
# stub _ismbckata_l(long ptr)
@ stub _ismbcl0(long)
# stub _ismbcl0_l(long ptr)
@ stub _ismbcl1(long)
# stub _ismbcl1_l(long ptr)
@ stub _ismbcl2(long)
# stub _ismbcl2_l(long ptr)
@ cdecl _ismbclegal(long)
# stub _ismbclegal_l(long ptr)
@ cdecl _ismbclower(long)
# stub _ismbclower_l(long ptr)
@ cdecl _ismbcprint(long)
# stub _ismbcprint_l(long ptr)
@ cdecl _ismbcpunct(long)
# stub _ismbcpunct_l(long ptr)
@ cdecl _ismbcspace(long)
# stub _ismbcspace_l(long ptr)
@ cdecl _ismbcsymbol(long)
# stub _ismbcsymbol_l(long ptr)
@ cdecl _ismbcupper(long)
# stub _ismbcupper_l(long ptr)
@ cdecl _ismbslead(ptr ptr)
# stub _ismbslead_l(long ptr)
@ cdecl _ismbstrail(ptr ptr)
# stub _ismbstrail_l(long ptr)
@ cdecl _isnan( double )
# stub -arch=win64 _isnanf(float)
@ cdecl _isprint_l(long ptr) MSVCRT__isprint_l
@ cdecl _isspace_l(long ptr) MSVCRT__isspace_l
@ cdecl _isupper_l(long ptr) MSVCRT__isupper_l
# stub _iswalnum_l(long ptr)
@ cdecl _iswalpha_l(long ptr) MSVCRT__iswalpha_l
# stub _iswcntrl_l(long ptr)
# stub _iswctype_l(long long ptr)
# stub _iswdigit_l(long ptr)
# stub _iswgraph_l(long ptr)
# stub _iswlower_l(long ptr)
# stub _iswprint_l(long ptr)
# stub _iswpunct_l(long ptr)
# stub _iswspace_l(long ptr)
# stub _iswupper_l(long ptr)
# stub _iswxdigit_l(long ptr)
@ cdecl _isxdigit_l(long ptr) MSVCRT__isxdigit_l
@ cdecl _itoa(long ptr long) ntdll._itoa
@ cdecl _itoa_s(long ptr long long)
@ cdecl _itow(long ptr long) ntdll._itow
@ cdecl _itow_s(long ptr long long)
@ cdecl _j0(double)
@ cdecl _j1(double)
@ cdecl _jn(long double)
@ cdecl _kbhit()
@ cdecl _lfind(ptr ptr ptr long ptr)
# stub _lfind_s(ptr ptr ptr long ptr ptr)
@ cdecl _loaddll(str)
@ cdecl -arch=x86_64 _local_unwind(ptr ptr)
@ cdecl -i386 _local_unwind2(ptr long)
@ cdecl -i386 _local_unwind4(ptr ptr long)
@ cdecl _localtime32(ptr) MSVCRT__localtime32
@ cdecl _localtime32_s(ptr ptr)
@ cdecl _localtime64(ptr) MSVCRT__localtime64
@ cdecl _localtime64_s(ptr ptr)
@ cdecl _lock(long)
@ cdecl _lock_file(ptr) MSVCRT__lock_file
@ cdecl _locking(long long long) MSVCRT__locking
@ cdecl _logb(double)
# stub _logbf(float)
@ cdecl -i386 _longjmpex(ptr long) MSVCRT_longjmp
@ cdecl _lrotl(long long) MSVCRT__lrotl
@ cdecl _lrotr(long long) MSVCRT__lrotr
@ cdecl _lsearch(ptr ptr ptr long ptr)
# stub _lsearch_s(ptr ptr ptr long ptr ptr)
@ cdecl _lseek(long long long) MSVCRT__lseek
@ cdecl -ret64 _lseeki64(long int64 long) MSVCRT__lseeki64
@ cdecl _ltoa(long ptr long) ntdll._ltoa
@ cdecl _ltoa_s(long ptr long long)
@ cdecl _ltow(long ptr long) ntdll._ltow
@ cdecl _ltow_s(long ptr long long)
@ cdecl _makepath(ptr str str str str)
@ cdecl _makepath_s(ptr long str str str str)
# stub _malloc_dbg(long long str long)
@ cdecl _matherr(ptr) MSVCRT__matherr
@ cdecl _mbbtombc(long)
# stub _mbbtombc_l(long ptr)
@ cdecl _mbbtype(long long)
# extern _mbcasemap
@ cdecl _mbccpy(ptr str)
# stub _mbccpy_l(ptr str ptr)
# stub _mbccpy_s(ptr long ptr str)
# stub _mbccpy_s_l(ptr long ptr str ptr)
@ cdecl _mbcjistojms (long)
# stub _mbcjistojms_l(long ptr)
@ stub _mbcjmstojis(long)
# stub _mbcjmstojis_l(long ptr)
@ cdecl _mbclen(ptr)
# stub _mbclen_l(ptr ptr)
@ stub _mbctohira(long)
# stub _mbctohira_l(long ptr)
@ stub _mbctokata(long)
# stub _mbctokata_l(long ptr)
@ cdecl _mbctolower(long)
# stub _mbctolower_l(long ptr)
@ cdecl _mbctombb(long)
# stub _mbctombb_l(long ptr)
@ cdecl _mbctoupper(long)
# stub _mbctoupper_l(long ptr)
@ extern _mbctype MSVCRT_mbctype
# stub _mblen_l(str long ptr)
@ cdecl _mbsbtype(str long)
# stub _mbsbtype_l(str long ptr)
@ cdecl _mbscat(str str)
# stub _mbscat_s(str long str)
# stub _mbscat_s_l(str long str ptr)
@ cdecl _mbschr(str long)
# stub _mbschr_l(str long ptr)
@ cdecl _mbscmp(str str)
# stub _mbscmp_l(str str ptr)
@ cdecl _mbscoll(str str)
# stub _mbscoll_l(str str ptr)
@ cdecl _mbscpy(ptr str)
# stub _mbscpy_s(ptr long str)
# stub _mbscpy_s_l(ptr long str ptr)
@ cdecl _mbscspn(str str)
# stub _mbscspn_l(str str ptr)
@ cdecl _mbsdec(ptr ptr)
# stub _mbsdec_l(ptr ptr ptr)
@ cdecl _mbsdup(str) _strdup
# stub _strdup_dbg(str long str long)
@ cdecl _mbsicmp(str str)
# stub _mbsicmp_l(str str ptr)
@ cdecl _mbsicoll(str str)
# stub _mbsicoll_l(str str ptr)
@ cdecl _mbsinc(str)
# stub _mbsinc_l(str ptr)
@ cdecl _mbslen(str)
# stub _mbslen_l(str ptr)
@ cdecl _mbslwr(str)
# stub _mbslwr_l(str ptr)
@ cdecl _mbslwr_s(str long)
# stub _mbslwr_s_l(str long ptr)
@ cdecl _mbsnbcat(str str long)
# stub _mbsnbcat_l(str str long ptr)
@ cdecl _mbsnbcat_s(str long ptr long)
# stub _mbsnbcat_s_l(str long ptr long ptr)
@ cdecl _mbsnbcmp(str str long)
# stub _mbsnbcmp_l(str str long ptr)
@ cdecl _mbsnbcnt(ptr long)
# stub _mbsnbcnt_l(ptr long ptr)
@ stub _mbsnbcoll(str str long)
# stub _mbsnbcoll_l(str str long ptr)
@ cdecl _mbsnbcpy(ptr str long)
# stub _mbsnbcpy_l(ptr str long ptr)
@ cdecl _mbsnbcpy_s(ptr long str long)
# stub _mbsnbcpy_s_l(ptr long str long ptr)
@ cdecl _mbsnbicmp(str str long)
# stub _mbsnbicmp_l(str str long ptr)
@ stub _mbsnbicoll(str str long)
# stub _mbsnbicoll_l(str str long ptr)
@ cdecl _mbsnbset(ptr long long)
# stub _mbsnbset_l(str long long ptr)
# stub _mbsnbset_s(ptr long long long)
# stub _mbsnbset_s_l(ptr long long long ptr)
@ cdecl _mbsncat(str str long)
# stub _mbsncat_l(str str long ptr)
# stub _mbsncat_s(str long str long)
# stub _mbsncat_s_l(str long str long ptr)
@ cdecl _mbsnccnt(str long)
# stub _mbsnccnt_l(str long ptr)
@ cdecl _mbsncmp(str str long)
# stub _mbsncmp_l(str str long ptr)
@ stub _mbsncoll(str str long)
# stub _mbsncoll_l(str str long ptr)
@ cdecl _mbsncpy(ptr str long)
# stub _mbsncpy_l(ptr str long ptr)
# stub _mbsncpy_s(ptr long str long)
# stub _mbsncpy_s_l(ptr long str long ptr)
@ cdecl _mbsnextc(str)
# stub _mbsnextc_l(str ptr)
@ cdecl _mbsnicmp(str str long)
# stub _mbsnicmp_l(str str long ptr)
@ stub _mbsnicoll(str str long)
# stub _mbsnicoll_l(str str long ptr)
@ cdecl _mbsninc(str long)
# stub _mbsninc_l(str long ptr)
# stub _mbsnlen(str long)
# stub _mbsnlen_l(str long ptr)
@ cdecl _mbsnset(ptr long long)
# stub _mbsnset_l(ptr long long ptr)
# stub _mbsnset_s(ptr long long long)
# stub _mbsnset_s_l(ptr long long long ptr)
@ cdecl _mbspbrk(str str)
# stub _mbspbrk_l(str str ptr)
@ cdecl _mbsrchr(str long)
# stub _mbsrchr_l(str long ptr)
@ cdecl _mbsrev(str)
# stub _mbsrev_l(str ptr)
@ cdecl _mbsset(ptr long)
# stub _mbsset_l(ptr long ptr)
# stub _mbsset_s(ptr long long)
# stub _mbsset_s_l(ptr long long ptr)
@ cdecl _mbsspn(str str)
# stub _mbsspn_l(str str ptr)
@ cdecl _mbsspnp(str str)
# stub _mbsspnp_l(str str ptr)
@ cdecl _mbsstr(str str)
# stub _mbsstr_l(str str ptr)
@ cdecl _mbstok(str str)
# stub _mbstok_l(str str ptr)
# stub _mbstok_s(str str ptr)
# stub _mbstok_s_l(str str ptr ptr)
@ cdecl _mbstowcs_l(ptr str long ptr) MSVCRT__mbstowcs_l
@ cdecl _mbstowcs_s_l(ptr ptr long str long ptr) MSVCRT__mbstowcs_s_l
@ cdecl _mbstrlen(str)
@ cdecl _mbstrlen_l(str ptr)
# stub _mbstrnlen(str long)
# stub _mbstrnlen_l(str long ptr)
@ cdecl _mbsupr(str)
# stub _mbsupr_l(str ptr)
@ cdecl _mbsupr_s(str long)
# stub _mbsupr_s_l(str long ptr)
# stub _mbtowc_l(ptr str long ptr)
@ cdecl _memccpy(ptr ptr long long) ntdll._memccpy
@ cdecl _memicmp(str str long) ntdll._memicmp
# stub _memicmp_l(str str long ptr)
@ cdecl _mkdir(str) MSVCRT__mkdir
@ cdecl _mkgmtime(ptr) MSVCRT__mkgmtime
@ cdecl _mkgmtime32(ptr) MSVCRT__mkgmtime32
@ cdecl _mkgmtime64(ptr) MSVCRT__mkgmtime64
@ cdecl _mktemp(str)
# stub _mktemp_s(str long)
@ cdecl _mktime32(ptr) MSVCRT__mktime32
@ cdecl _mktime64(ptr) MSVCRT__mktime64
@ cdecl _msize(ptr)
# stub -arch=win32 _msize_debug(ptr long)
# stub -arch=win64 _msize_dbg(ptr long)
@ cdecl _nextafter(double double)
# stub -arch=win64 _nextafterf(float float)
@ cdecl _onexit(ptr) MSVCRT__onexit
@ varargs _open(str long) MSVCRT__open
@ cdecl _open_osfhandle(long long)
@ extern _osplatform MSVCRT__osplatform
@ extern _osver MSVCRT__osver
@ stub -arch=i386 _outp(long long)
@ stub -arch=i386 _outpd(long long)
@ stub -arch=i386 _outpw(long long)
@ cdecl _pclose (ptr) MSVCRT__pclose
@ extern _pctype MSVCRT__pctype
@ extern _pgmptr MSVCRT__pgmptr
@ cdecl _pipe (ptr long long) MSVCRT__pipe
@ cdecl _popen (str str) MSVCRT__popen
# stub _printf_l(str ptr)
# stub _printf_p(str)
# stub _printf_p_l(str ptr)
# stub _printf_s_l(str ptr)
@ cdecl _purecall()
@ cdecl _putch(long)
@ cdecl _putenv(str)
@ cdecl _putenv_s(str str)
@ cdecl _putw(long ptr) MSVCRT__putw
@ cdecl _putwch(long) MSVCRT__putwch
@ cdecl _putws(wstr)
# extern _pwctype
@ cdecl _read(long ptr long) MSVCRT__read
# stub _realloc_dbg(ptr long long str long)
@ cdecl _resetstkoflw()
@ cdecl _rmdir(str) MSVCRT__rmdir
@ cdecl _rmtmp()
@ cdecl _rotl(long long)
@ cdecl -ret64 _rotl64(int64 long)
@ cdecl _rotr(long long)
@ cdecl -ret64 _rotr64(int64 long)
@ cdecl -arch=i386 _safe_fdiv()
@ cdecl -arch=i386 _safe_fdivr()
@ cdecl -arch=i386 _safe_fprem()
@ cdecl -arch=i386 _safe_fprem1()
@ cdecl _scalb(double long) MSVCRT__scalb
@ cdecl -arch=x86_64 _scalbf(float long) MSVCRT__scalbf
@ varargs _scanf_l(str ptr) MSVCRT__scanf_l
@ varargs _scanf_s_l(str ptr) MSVCRT__scanf_s_l
@ varargs _scprintf(str) MSVCRT__scprintf
# stub _scprintf_l(str ptr)
# stub _scprintf_p_l(str ptr)
@ varargs _scwprintf(wstr) MSVCRT__scwprintf
# stub _scwprintf_l(wstr ptr)
# stub _scwprintf_p_l(wstr ptr)
@ cdecl _searchenv(str str ptr)
@ cdecl _searchenv_s(str str ptr long)
@ stdcall -i386 _seh_longjmp_unwind4(ptr)
@ stdcall -i386 _seh_longjmp_unwind(ptr)
@ cdecl _set_SSE2_enable(long) MSVCRT__set_SSE2_enable
@ cdecl _set_controlfp(long long)
@ cdecl _set_doserrno(long)
@ cdecl _set_errno(long)
@ cdecl _set_error_mode(long)
# stub _set_fileinfo(long)
# stub _set_fmode(long)
# stub _set_output_format(long)
@ cdecl _set_sbh_threshold(long)
@ cdecl _seterrormode(long)
@ cdecl -arch=i386,x86_64 -norelay _setjmp(ptr) MSVCRT__setjmp
@ cdecl -arch=i386 -norelay _setjmp3(ptr long) MSVCRT__setjmp3
@ cdecl -arch=x86_64 -norelay _setjmpex(ptr ptr) MSVCRT__setjmpex
@ cdecl _setmaxstdio(long)
@ cdecl _setmbcp(long)
@ cdecl _setmode(long long)
@ stub _setsystime(ptr long)
@ cdecl _sleep(long) MSVCRT__sleep
@ varargs _snprintf(ptr long str) MSVCRT__snprintf
# stub _snprintf_c(ptr long str)
# stub _snprintf_c_l(ptr long str ptr)
# stub _snprintf_l(ptr long str ptr)
@ varargs _snprintf_s(ptr long long str) MSVCRT__snprintf_s
# stub _snprintf_s_l(ptr long long str ptr)
@ varargs _snscanf(str long str) MSVCRT__snscanf
@ varargs _snscanf_l(str long str ptr) MSVCRT__snscanf_l
@ varargs _snscanf_s(str long str) MSVCRT__snscanf_s
@ varargs _snscanf_s_l(str long str ptr) MSVCRT__snscanf_s_l
@ varargs _snwprintf(ptr long wstr) MSVCRT__snwprintf
# stub _snwprintf_l(ptr long wstr ptr)
@ varargs _snwprintf_s(ptr long long wstr) MSVCRT__snwprintf_s
# stub _snwprintf_s_l(ptr long long wstr ptr)
@ varargs _snwscanf(wstr long wstr) MSVCRT__snwscanf
@ varargs _snwscanf_l(wstr long wstr ptr) MSVCRT__snwscanf_l
@ varargs _snwscanf_s(wstr long wstr) MSVCRT__snwscanf_s
@ varargs _snwscanf_s_l(wstr long wstr ptr) MSVCRT__snwscanf_s_l
@ varargs _sopen(str long long) MSVCRT__sopen
@ cdecl _sopen_s(ptr str long long long) MSVCRT__sopen_s
@ varargs _spawnl(long str str)
@ varargs _spawnle(long str str)
@ varargs _spawnlp(long str str)
@ varargs _spawnlpe(long str str)
@ cdecl _spawnv(long str ptr)
@ cdecl _spawnve(long str ptr ptr) MSVCRT__spawnve
@ cdecl _spawnvp(long str ptr)
@ cdecl _spawnvpe(long str ptr ptr) MSVCRT__spawnvpe
@ cdecl _splitpath(str ptr ptr ptr ptr)
@ cdecl _splitpath_s(str ptr long ptr long ptr long ptr long)
# stub _sprintf_l(ptr str ptr)
@ varargs _sprintf_p_l(ptr long str ptr) MSVCRT_sprintf_p_l
# stub _sprintf_s_l(ptr long str ptr)
@ varargs _sscanf_l(str str ptr) MSVCRT__sscanf_l
@ varargs _sscanf_s_l(str str ptr) MSVCRT__sscanf_s_l
@ cdecl _stat(str ptr) MSVCRT_stat
@ cdecl _stat64(str ptr) MSVCRT_stat64
@ cdecl _stati64(str ptr) MSVCRT_stati64
@ cdecl _statusfp()
@ cdecl _strcmpi(str str) ntdll._strcmpi
@ cdecl _strcoll_l(str str ptr) MSVCRT_strcoll_l
@ cdecl _strdate(ptr)
@ cdecl _strdate_s(ptr long)
@ cdecl _strdup(str)
# stub _strdup_dbg(str long str long)
@ cdecl _strerror(long)
# stub _strerror_s(ptr long long)
@ cdecl _stricmp(str str) ntdll._stricmp
# stub _stricmp_l(str str ptr)
@ cdecl _stricoll(str str) MSVCRT__stricoll
@ cdecl _stricoll_l(str str ptr) MSVCRT__stricoll_l
@ cdecl _strlwr(str)
@ cdecl _strlwr_l(str ptr)
@ cdecl _strlwr_s(ptr long)
@ cdecl _strlwr_s_l(ptr long ptr)
@ cdecl _strncoll(str str long) MSVCRT_strncoll_l
@ cdecl _strncoll_l(str str long ptr) MSVCRT_strncoll
@ cdecl _strnicmp(str str long) ntdll._strnicmp
# stub _strnicmp_l(str str long ptr)
@ cdecl _strnicoll(str str long) MSVCRT__strnicoll
@ cdecl _strnicoll_l(str str long ptr) MSVCRT__strnicoll_l
@ cdecl _strnset(str long long) MSVCRT__strnset
# stub _strnset_s(str long long long)
@ cdecl _strrev(str)
@ cdecl _strset(str long)
# stub _strset_s(str long long)
@ cdecl _strtime(ptr)
@ cdecl _strtime_s(ptr long)
@ cdecl _strtod_l(str ptr ptr) MSVCRT_strtod_l
@ cdecl -ret64 _strtoi64(str ptr long) MSVCRT_strtoi64
@ cdecl -ret64 _strtoi64_l(str ptr long ptr) MSVCRT_strtoi64_l
# stub _strtol_l(str ptr long ptr)
@ cdecl -ret64 _strtoui64(str ptr long) MSVCRT_strtoui64
@ cdecl -ret64 _strtoui64_l(str ptr long ptr) MSVCRT_strtoui64_l
# stub _strtoul_l(str ptr long ptr)
@ cdecl _strupr(str)
@ cdecl _strupr_l(str ptr)
@ cdecl _strupr_s(str long)
@ cdecl _strupr_s_l(str long ptr)
# stub _strxfrm_l(ptr str long ptr)
@ cdecl _swab(str str long) MSVCRT__swab
@ varargs _swprintf(ptr wstr) MSVCRT_swprintf
# stub _swprintf_c(ptr long str)
# stub _swprintf_c_l(ptr long str ptr)
@ varargs _swprintf_p_l(ptr long wstr ptr) MSVCRT_swprintf_p_l
# stub _swprintf_s_l(ptr long str ptr)
@ varargs _swscanf_l(wstr wstr ptr) MSVCRT__swscanf_l
@ varargs _swscanf_s_l(wstr wstr ptr) MSVCRT__swscanf_s_l
@ extern _sys_errlist MSVCRT__sys_errlist
@ extern _sys_nerr MSVCRT__sys_nerr
@ cdecl _tell(long) MSVCRT__tell
@ cdecl -ret64 _telli64(long)
@ cdecl _tempnam(str str)
# stub _tempnam_dbg(str str long str long)
@ cdecl _time32(ptr) MSVCRT__time32
@ cdecl _time64(ptr) MSVCRT__time64
@ extern _timezone MSVCRT___timezone
@ cdecl _tolower(long) MSVCRT__tolower
@ cdecl _tolower_l(long ptr) MSVCRT__tolower_l
@ cdecl _toupper(long) MSVCRT__toupper
@ cdecl _toupper_l(long ptr) MSVCRT__toupper_l
@ cdecl _towlower_l(long ptr) MSVCRT__towlower_l
@ cdecl _towupper_l(long ptr) MSVCRT__towupper_l
@ extern _tzname MSVCRT__tzname
@ cdecl _tzset() MSVCRT__tzset
@ cdecl _ui64toa(int64 ptr long) ntdll._ui64toa
@ cdecl _ui64toa_s(int64 ptr long long) MSVCRT__ui64toa_s
@ cdecl _ui64tow(int64 ptr long) ntdll._ui64tow
@ cdecl _ui64tow_s(int64 ptr long long) MSVCRT__ui64tow_s
@ cdecl _ultoa(long ptr long) ntdll._ultoa
@ cdecl _ultoa_s(long ptr long long)
@ cdecl _ultow(long ptr long) ntdll._ultow
# stub _ultow_s(long ptr long long)
@ cdecl _umask(long) MSVCRT__umask
# stub _umask_s(long ptr)
@ cdecl _ungetch(long)
# stub _ungetwch(long)
@ cdecl _unlink(str) MSVCRT__unlink
@ cdecl _unloaddll(long)
@ cdecl _unlock(long)
@ cdecl _unlock_file(ptr) MSVCRT__unlock_file
@ cdecl _utime32(str ptr)
@ cdecl _utime64(str ptr)
@ cdecl _vcprintf(str ptr)
# stub _vcprintf_l(str ptr ptr)
# stub _vcprintf_p(str ptr)
# stub _vcprintf_p_l(str ptr ptr)
# stub _vcprintf_s(str ptr)
# stub _vcprintf_s_l(str ptr ptr)
@ cdecl _vcwprintf(wstr ptr)
# stub _vcwprintf_l(wstr ptr ptr)
# stub _vcwprintf_p(wstr ptr)
# stub _vcwprintf_p_l(wstr ptr ptr)
# stub _vcwprintf_s(wstr ptr)
# stub _vcwprintf_s_l(wstr ptr ptr)
# stub _vfprintf_l(ptr str ptr ptr)
# stub _vfprintf_p(ptr str ptr)
# stub _vfprintf_p_l(ptr str ptr ptr)
# stub _vfprintf_s_l(ptr str ptr ptr)
# stub _vfwprintf_l(ptr wstr ptr ptr)
# stub _vfwprintf_p(ptr wstr ptr)
# stub _vfwprintf_p_l(ptr wstr ptr ptr)
# stub _vfwprintf_s_l(ptr wstr ptr ptr)
# stub _vprintf_l(str ptr ptr)
# stub _vprintf_p(str ptr)
# stub _vprintf_p_l(str ptr ptr)
# stub _vprintf_s_l(str ptr ptr)
@ cdecl _utime(str ptr)
@ cdecl _vscprintf(str ptr)
# stub _vscprintf_l(str ptr ptr)
# stub _vscprintf_p_l(str ptr ptr)
@ cdecl _vscwprintf(wstr ptr)
# stub _vscwprintf_l(wstr ptr ptr)
# stub _vscwprintf_p_l(wstr ptr ptr)
@ cdecl _vsnprintf(ptr long str ptr) MSVCRT_vsnprintf
@ cdecl _vsnprintf_c(ptr long str ptr) MSVCRT_vsnprintf
@ cdecl _vsnprintf_c_l(ptr long str ptr ptr) MSVCRT_vsnprintf_l
@ cdecl _vsnprintf_l(ptr long str ptr ptr) MSVCRT_vsnprintf_l
@ cdecl _vsnprintf_s(ptr long long str ptr) MSVCRT_vsnprintf_s
@ cdecl _vsnprintf_s_l(ptr long long str ptr ptr) MSVCRT_vsnprintf_s_l
@ cdecl _vsnwprintf(ptr long wstr ptr) MSVCRT_vsnwprintf
@ cdecl _vsnwprintf_l(ptr long wstr ptr ptr) MSVCRT_vsnwprintf_l
@ cdecl _vsnwprintf_s(ptr long long wstr ptr) MSVCRT_vsnwprintf_s
@ cdecl _vsnwprintf_s_l(ptr long long wstr ptr ptr) MSVCRT_vsnwprintf_s_l
# stub _vsprintf_l(ptr str ptr ptr)
@ cdecl _vsprintf_p(ptr long str ptr) MSVCRT_vsprintf_p
@ cdecl _vsprintf_p_l(ptr long str ptr ptr) MSVCRT_vsprintf_p_l
# stub _vsprintf_s_l(ptr long str ptr ptr)
@ cdecl _vswprintf(ptr long wstr ptr) MSVCRT_vsnwprintf
@ cdecl _vswprintf_c(ptr long wstr ptr) MSVCRT_vsnwprintf
@ cdecl _vswprintf_c_l(ptr long wstr ptr ptr) MSVCRT_vsnwprintf_l
@ cdecl _vswprintf_l(ptr long wstr ptr ptr) MSVCRT_vsnwprintf_l
@ cdecl _vswprintf_p_l(ptr long wstr ptr ptr) MSVCRT_vswprintf_p_l
@ cdecl _vswprintf_s_l(ptr long wstr ptr ptr) MSVCRT_vswprintf_s_l
# stub _vwprintf_l(wstr ptr ptr)
# stub _vwprintf_p(wstr ptr)
# stub _vwprintf_p_l(wstr ptr ptr)
# stub _vwprintf_s_l(wstr ptr ptr)
@ cdecl _waccess(wstr long)
@ cdecl _waccess_s(wstr long)
@ cdecl _wasctime(ptr) MSVCRT__wasctime
# stub _wasctime_s(ptr long ptr)
@ cdecl _wassert(wstr wstr long) MSVCRT__wassert
@ cdecl _wchdir(wstr)
@ cdecl _wchmod(wstr long)
@ extern _wcmdln MSVCRT__wcmdln
@ cdecl _wcreat(wstr long)
# stub _wcscoll_l(wstr wstr ptr)
@ cdecl _wcsdup(wstr)
# stub _wcsdup_dbg(wstr long str long)
@ cdecl _wcserror(long)
@ cdecl _wcserror_s(ptr long long)
# stub _wcsftime_l(ptr long wstr ptr ptr)
@ cdecl _wcsicmp(wstr wstr) ntdll._wcsicmp
# stub _wcsicmp_l(wstr wstr ptr)
@ cdecl _wcsicoll(wstr wstr)
# stub _wcsicoll_l(wstr wstr ptr)
@ cdecl _wcslwr(wstr) ntdll._wcslwr
# stub _wcslwr_l(wstr ptr)
@ cdecl _wcslwr_s(wstr long) MSVCRT__wcslwr_s
# stub _wcslwr_s_l(wstr long ptr)
@ stub _wcsncoll(wstr wstr long)
# stub _wcsncoll_l(wstr wstr long ptr)
@ cdecl _wcsnicmp(wstr wstr long) ntdll._wcsnicmp
# stub _wcsnicmp_l(wstr wstr long ptr)
@ cdecl _wcsnicoll(wstr wstr long)
# stub _wcsnicoll_l(wstr wstr long ptr)
@ cdecl _wcsnset(wstr long long) MSVCRT__wcsnset
# stub _wcsnset_s(wstr long long)
@ cdecl _wcsrev(wstr)
@ cdecl _wcsset(wstr long)
# stub _wcsset_s(wstr long)
@ cdecl -ret64 _wcstoi64(wstr ptr long) MSVCRT__wcstoi64
@ cdecl -ret64 _wcstoi64_l(wstr ptr long ptr) MSVCRT__wcstoi64_l
# stub _wcstol_l(wstr ptr long ptr)
@ cdecl _wcstombs_l(ptr ptr long ptr) MSVCRT__wcstombs_l
@ cdecl _wcstombs_s_l(ptr ptr long wstr long ptr) MSVCRT__wcstombs_s_l
@ cdecl -ret64 _wcstoui64(wstr ptr long) MSVCRT__wcstoui64
@ cdecl -ret64 _wcstoui64_l(wstr ptr long ptr) MSVCRT__wcstoui64_l
# stub _wcstoul_l(wstr ptr long ptr)
@ cdecl _wcsupr(wstr) ntdll._wcsupr
# stub _wcsupr_l(wstr ptr)
@ cdecl _wcsupr_s(wstr long) MSVCRT__wcsupr_s
@ cdecl _wcsupr_s_l(wstr long ptr) MSVCRT__wcsupr_s_l
# stub _wcsxfrm_l(ptr wstr long ptr)
@ cdecl _wctime(ptr) MSVCRT__wctime
@ cdecl _wctime32(ptr) MSVCRT__wctime32
# stub _wctime32_s(ptr long ptr)
@ cdecl _wctime64(ptr) MSVCRT__wctime64
# stub _wctime64_s(ptr long ptr)
# stub _wctomb_l(ptr long ptr)
# stub _wctomb_s_l(ptr ptr long long ptr)
# extern _wctype
@ extern _wenviron MSVCRT__wenviron
@ varargs _wexecl(wstr wstr)
@ varargs _wexecle(wstr wstr)
@ varargs _wexeclp(wstr wstr)
@ varargs _wexeclpe(wstr wstr)
@ cdecl _wexecv(wstr ptr)
@ cdecl _wexecve(wstr ptr ptr)
@ cdecl _wexecvp(wstr ptr)
@ cdecl _wexecvpe(wstr ptr ptr)
@ cdecl _wfdopen(long wstr) MSVCRT__wfdopen
@ cdecl _wfindfirst(wstr ptr) MSVCRT__wfindfirst
@ cdecl _wfindfirst64(wstr ptr) MSVCRT__wfindfirst64
@ cdecl _wfindfirsti64(wstr ptr) MSVCRT__wfindfirsti64
@ cdecl _wfindfirst64i32(wstr ptr) MSVCRT__wfindfirst64i32
@ cdecl _wfindnext(long ptr) MSVCRT__wfindnext
@ cdecl _wfindnext64(long ptr) MSVCRT__wfindnext64
@ cdecl _wfindnext64i32(long ptr) MSVCRT__wfindnext64i32
@ cdecl _wfindnexti64(long ptr) MSVCRT__wfindnexti64
@ cdecl _wfopen(wstr wstr) MSVCRT__wfopen
@ cdecl _wfopen_s(ptr wstr wstr) MSVCRT__wfopen_s
@ cdecl _wfreopen(wstr wstr ptr) MSVCRT__wfreopen
# stub _wfreopen_s(ptr wstr wstr ptr)
@ cdecl _wfsopen(wstr wstr long) MSVCRT__wfsopen
@ cdecl _wfullpath(ptr wstr long)
# stub _wfullpath_dbg(ptr wstr long long str long)
@ cdecl _wgetcwd(wstr long)
@ cdecl _wgetdcwd(long wstr long)
@ cdecl _wgetenv(wstr)
@ cdecl _wgetenv_s(ptr ptr long wstr)
@ extern _winmajor MSVCRT__winmajor
@ extern _winminor MSVCRT__winminor
# stub _winput_s
@ extern _winver MSVCRT__winver
@ cdecl _wmakepath(ptr wstr wstr wstr wstr)
@ cdecl _wmakepath_s(ptr long wstr wstr wstr wstr)
@ cdecl _wmkdir(wstr)
@ cdecl _wmktemp(wstr)
# stub _wmktemp_s(wstr long)
@ varargs _wopen(wstr long)
# stub _woutput_s
@ stub _wperror(wstr)
@ extern _wpgmptr MSVCRT__wpgmptr
@ cdecl _wpopen (wstr wstr) MSVCRT__wpopen
# stub _wprintf_l(wstr ptr)
# stub _wprintf_p(wstr)
# stub _wprintf_p_l(wstr ptr)
# stub _wprintf_s_l(wstr ptr)
@ cdecl _wputenv(wstr)
@ cdecl _wputenv_s(wstr wstr)
@ cdecl _wremove(wstr)
@ cdecl _wrename(wstr wstr)
@ cdecl _write(long ptr long) MSVCRT__write
@ cdecl _wrmdir(wstr)
@ varargs _wscanf_l(wstr ptr) MSVCRT__wscanf_l
@ varargs _wscanf_s_l(wstr ptr) MSVCRT__wscanf_s_l
@ cdecl _wsearchenv(wstr wstr ptr)
@ cdecl _wsearchenv_s(wstr wstr ptr long)
@ cdecl _wsetlocale(long wstr) MSVCRT__wsetlocale
@ varargs _wsopen(wstr long long) MSVCRT__wsopen
@ cdecl _wsopen_s(ptr wstr long long long) MSVCRT__wsopen_s
@ varargs _wspawnl(long wstr wstr)
@ varargs _wspawnle(long wstr wstr)
@ varargs _wspawnlp(long wstr wstr)
@ varargs _wspawnlpe(long wstr wstr)
@ cdecl _wspawnv(long wstr ptr)
@ cdecl _wspawnve(long wstr ptr ptr)
@ cdecl _wspawnvp(long wstr ptr)
@ cdecl _wspawnvpe(long wstr ptr ptr)
@ cdecl _wsplitpath(wstr ptr ptr ptr ptr)
@ cdecl _wsplitpath_s(wstr ptr long ptr long ptr long ptr long) _wsplitpath_s
@ cdecl _wstat(wstr ptr) MSVCRT__wstat
@ cdecl _wstati64(wstr ptr) MSVCRT__wstati64
@ cdecl _wstat64(wstr ptr) MSVCRT__wstat64
@ cdecl _wstrdate(ptr)
@ cdecl _wstrdate_s(ptr long)
@ cdecl _wstrtime(ptr)
@ cdecl _wstrtime_s(ptr long)
@ cdecl _wsystem(wstr)
@ cdecl _wtempnam(wstr wstr)
# stub _wtempnam_dbg(wstr wstr long str long)
@ cdecl _wtmpnam(ptr) MSVCRT_wtmpnam
# stub _wtmpnam_s(ptr long)
@ cdecl _wtof(wstr) MSVCRT__wtof
@ cdecl _wtof_l(wstr ptr) MSVCRT__wtof_l
@ cdecl _wtoi(wstr) ntdll._wtoi
@ cdecl -ret64 _wtoi64(wstr) ntdll._wtoi64
# stub -ret64 _wtoi64_l(wstr ptr)
# stub _wtoi_l(wstr ptr)
@ cdecl _wtol(wstr) ntdll._wtol
# stub _wtol_l(wstr ptr)
@ cdecl _wunlink(wstr)
@ cdecl _wutime(wstr ptr)
@ cdecl _wutime32(wstr ptr)
@ cdecl _wutime64(wstr ptr)
@ cdecl _y0(double)
@ cdecl _y1(double)
@ cdecl _yn(long double )
@ cdecl abort() MSVCRT_abort
@ cdecl abs(long) MSVCRT_abs
@ cdecl acos(double) MSVCRT_acos
@ cdecl -arch=x86_64 acosf(float) MSVCRT_acosf
@ cdecl asctime(ptr) MSVCRT_asctime
# stub asctime_s(ptr long ptr)
@ cdecl asin(double) MSVCRT_asin
@ cdecl atan(double) MSVCRT_atan
@ cdecl atan2(double double) MSVCRT_atan2
@ cdecl -arch=x86_64 asinf(float) MSVCRT_asinf
@ cdecl -arch=x86_64 atanf(float) MSVCRT_atanf
@ cdecl -arch=x86_64 atan2f(float float) MSVCRT_atan2f
@ cdecl atexit(ptr) MSVCRT_atexit
@ cdecl atof(str) MSVCRT_atof
@ cdecl atoi(str) ntdll.atoi
@ cdecl atol(str) ntdll.atol
@ cdecl bsearch(ptr ptr long long ptr) ntdll.bsearch
# stub bsearch_s(ptr ptr long long ptr ptr)
@ cdecl btowc(long) MSVCRT_btowc
@ cdecl calloc(long long) MSVCRT_calloc
@ cdecl ceil(double) MSVCRT_ceil
@ cdecl -arch=x86_64 ceilf(float) MSVCRT_ceilf
@ cdecl clearerr(ptr) MSVCRT_clearerr
# stub clearerr_s(ptr)
@ cdecl clock() MSVCRT_clock
@ cdecl cos(double) MSVCRT_cos
@ cdecl cosh(double) MSVCRT_cosh
@ cdecl -arch=x86_64 cosf(float) MSVCRT_cosf
@ cdecl -arch=x86_64 coshf(float) MSVCRT_coshf
@ cdecl ctime(ptr) MSVCRT_ctime
@ cdecl difftime(long long) MSVCRT_difftime
@ cdecl -ret64 div(long long) MSVCRT_div
@ cdecl exit(long) MSVCRT_exit
@ cdecl exp(double) MSVCRT_exp
@ cdecl -arch=x86_64 expf(float) MSVCRT_expf
@ cdecl fabs(double) MSVCRT_fabs
@ cdecl fclose(ptr) MSVCRT_fclose
@ cdecl feof(ptr) MSVCRT_feof
@ cdecl ferror(ptr) MSVCRT_ferror
@ cdecl fflush(ptr) MSVCRT_fflush
@ cdecl fgetc(ptr) MSVCRT_fgetc
@ cdecl fgetpos(ptr ptr) MSVCRT_fgetpos
@ cdecl fgets(ptr long ptr) MSVCRT_fgets
@ cdecl fgetwc(ptr) MSVCRT_fgetwc
@ cdecl fgetws(ptr long ptr) MSVCRT_fgetws
@ cdecl floor(double) MSVCRT_floor
@ cdecl -arch=x86_64 floorf(float) MSVCRT_floorf
@ cdecl fmod(double double) MSVCRT_fmod
@ cdecl -arch=x86_64 fmodf(float float) MSVCRT_fmodf
@ cdecl fopen(str str) MSVCRT_fopen
@ cdecl fopen_s(ptr str str) MSVCRT_fopen_s
@ varargs fprintf(ptr str) MSVCRT_fprintf
@ varargs fprintf_s(ptr str) MSVCRT_fprintf_s
@ cdecl fputc(long ptr) MSVCRT_fputc
@ cdecl fputs(str ptr) MSVCRT_fputs
@ cdecl fputwc(long ptr) MSVCRT_fputwc
@ cdecl fputws(wstr ptr) MSVCRT_fputws
@ cdecl fread(ptr long long ptr) MSVCRT_fread
@ cdecl free(ptr) MSVCRT_free
@ cdecl freopen(str str ptr) MSVCRT_freopen
# stub freopen_s(ptr str str ptr)
@ cdecl frexp(double ptr) MSVCRT_frexp
@ cdecl -arch=x86_64 frexpf(float ptr) MSVCRT_frexpf
@ varargs fscanf(ptr str) MSVCRT_fscanf
@ varargs fscanf_s(ptr str) MSVCRT_fscanf_s
@ cdecl fseek(ptr long long) MSVCRT_fseek
@ cdecl fsetpos(ptr ptr) MSVCRT_fsetpos
@ cdecl ftell(ptr) MSVCRT_ftell
@ varargs fwprintf(ptr wstr) MSVCRT_fwprintf
@ varargs fwprintf_s(ptr wstr) MSVCRT_fwprintf_s
@ cdecl fwrite(ptr long long ptr) MSVCRT_fwrite
@ varargs fwscanf(ptr wstr) MSVCRT_fwscanf
@ varargs fwscanf_s(ptr wstr) MSVCRT_fwscanf_s
@ cdecl getc(ptr) MSVCRT_getc
@ cdecl getchar() MSVCRT_getchar
@ cdecl getenv(str) MSVCRT_getenv
@ cdecl getenv_s(ptr ptr long str)
@ cdecl gets(str) MSVCRT_gets
@ cdecl getwc(ptr) MSVCRT_getwc
@ cdecl getwchar() MSVCRT_getwchar
@ cdecl gmtime(ptr) MSVCRT_gmtime
@ cdecl is_wctype(long long) ntdll.iswctype
@ cdecl isalnum(long) MSVCRT_isalnum
@ cdecl isalpha(long) MSVCRT_isalpha
@ cdecl iscntrl(long) MSVCRT_iscntrl
@ cdecl isdigit(long) MSVCRT_isdigit
@ cdecl isgraph(long) MSVCRT_isgraph
@ cdecl isleadbyte(long) MSVCRT_isleadbyte
@ cdecl islower(long) MSVCRT_islower
@ cdecl isprint(long) MSVCRT_isprint
@ cdecl ispunct(long) MSVCRT_ispunct
@ cdecl isspace(long) MSVCRT_isspace
@ cdecl isupper(long) MSVCRT_isupper
@ cdecl iswalnum(long) MSVCRT_iswalnum
@ cdecl iswalpha(long) ntdll.iswalpha
@ cdecl iswascii(long) MSVCRT_iswascii
@ cdecl iswcntrl(long) MSVCRT_iswcntrl
@ cdecl iswctype(long long) ntdll.iswctype
@ cdecl iswdigit(long) MSVCRT_iswdigit
@ cdecl iswgraph(long) MSVCRT_iswgraph
@ cdecl iswlower(long) MSVCRT_iswlower
@ cdecl iswprint(long) MSVCRT_iswprint
@ cdecl iswpunct(long) MSVCRT_iswpunct
@ cdecl iswspace(long) MSVCRT_iswspace
@ cdecl iswupper(long) MSVCRT_iswupper
@ cdecl iswxdigit(long) MSVCRT_iswxdigit
@ cdecl isxdigit(long) MSVCRT_isxdigit
@ cdecl labs(long) MSVCRT_labs
@ cdecl ldexp( double long) MSVCRT_ldexp
@ cdecl ldiv(long long) MSVCRT_ldiv
@ cdecl localeconv() MSVCRT_localeconv
@ cdecl localtime(ptr) MSVCRT_localtime
@ cdecl log(double) MSVCRT_log
@ cdecl log10(double) MSVCRT_log10
@ cdecl -arch=x86_64 logf(float) MSVCRT_logf
@ cdecl -arch=x86_64 log10f(float) MSVCRT_log10f
@ cdecl -arch=i386,x86_64 longjmp(ptr long) MSVCRT_longjmp
@ cdecl malloc(long) MSVCRT_malloc
@ cdecl mblen(ptr long) MSVCRT_mblen
# stub mbrlen(ptr long ptr)
# stub mbrtowc(ptr str long ptr)
# stub mbsdup_dbg(wstr long ptr long)
# stub mbsrtowcs(ptr ptr long ptr)
# stub mbsrtowcs_s(ptr ptr long ptr long ptr)
@ cdecl mbstowcs(ptr str long) MSVCRT_mbstowcs
@ cdecl mbstowcs_s(ptr ptr long str long) MSVCRT__mbstowcs_s
@ cdecl mbtowc(ptr str long) MSVCRT_mbtowc
@ cdecl memchr(ptr long long) ntdll.memchr
@ cdecl memcmp(ptr ptr long) ntdll.memcmp
@ cdecl memcpy(ptr ptr long) ntdll.memcpy
@ cdecl memcpy_s(ptr long ptr long) memmove_s
@ cdecl memmove(ptr ptr long) ntdll.memmove
@ cdecl memmove_s(ptr long ptr long)
@ cdecl memset(ptr long long) ntdll.memset
@ cdecl mktime(ptr) MSVCRT_mktime
@ cdecl modf(double ptr) MSVCRT_modf
@ cdecl -arch=x86_64 modff(float ptr) MSVCRT_modff
@ cdecl perror(str) MSVCRT_perror
@ cdecl pow(double double) MSVCRT_pow
@ cdecl -arch=x86_64 powf(float float) MSVCRT_powf
@ varargs printf(str) MSVCRT_printf
@ varargs printf_s(str) MSVCRT_printf_s
@ cdecl putc(long ptr) MSVCRT_putc
@ cdecl putchar(long) MSVCRT_putchar
@ cdecl puts(str) MSVCRT_puts
@ cdecl putwc(long ptr) MSVCRT_fputwc
@ cdecl putwchar(long) _fputwchar
@ cdecl qsort(ptr long long ptr) ntdll.qsort
@ cdecl qsort_s(ptr long long ptr ptr) MSVCRT_qsort_s
@ cdecl raise(long) MSVCRT_raise
@ cdecl rand() MSVCRT_rand
@ cdecl rand_s(ptr) MSVCRT_rand_s
@ cdecl realloc(ptr long) MSVCRT_realloc
@ cdecl remove(str) MSVCRT_remove
@ cdecl rename(str str) MSVCRT_rename
@ cdecl rewind(ptr) MSVCRT_rewind
@ varargs scanf(str) MSVCRT_scanf
@ varargs scanf_s(str) MSVCRT_scanf_s
@ cdecl setbuf(ptr ptr) MSVCRT_setbuf
@ cdecl -arch=x86_64 -norelay -private setjmp(ptr) MSVCRT__setjmp
@ cdecl setlocale(long str) MSVCRT_setlocale
@ cdecl setvbuf(ptr str long long) MSVCRT_setvbuf
@ cdecl signal(long long) MSVCRT_signal
@ cdecl sin(double) MSVCRT_sin
@ cdecl sinh(double) MSVCRT_sinh
@ cdecl -arch=x86_64 sinf(float) MSVCRT_sinf
@ cdecl -arch=x86_64 sinhf(float) MSVCRT_sinhf
@ varargs sprintf(ptr str) MSVCRT_sprintf
@ varargs sprintf_s(ptr long str) MSVCRT_sprintf_s
@ cdecl sqrt(double) MSVCRT_sqrt
@ cdecl -arch=x86_64 sqrtf(float) MSVCRT_sqrtf
@ cdecl srand(long) MSVCRT_srand
@ varargs sscanf(str str) MSVCRT_sscanf
@ varargs sscanf_s(str str) MSVCRT_sscanf_s
@ cdecl strcat(str str) ntdll.strcat
@ cdecl strcat_s(str long str) MSVCRT_strcat_s
@ cdecl strchr(str long) ntdll.strchr
@ cdecl strcmp(str str) ntdll.strcmp
@ cdecl strcoll(str str) MSVCRT_strcoll
@ cdecl strcpy(ptr str) ntdll.strcpy
@ cdecl strcpy_s(ptr long str) MSVCRT_strcpy_s
@ cdecl strcspn(str str) ntdll.strcspn
@ cdecl strerror(long) MSVCRT_strerror
@ cdecl strerror_s(ptr long long)
@ cdecl strftime(str long str ptr) MSVCRT_strftime
@ cdecl strlen(str) ntdll.strlen
@ cdecl strncat(str str long) ntdll.strncat
@ cdecl strncat_s(str long str long) MSVCRT_strncat_s
@ cdecl strncmp(str str long) ntdll.strncmp
@ cdecl strncpy(ptr str long) ntdll.strncpy
@ cdecl strncpy_s(ptr long str long)
@ cdecl strnlen(str long) MSVCRT_strnlen
@ cdecl strpbrk(str str) ntdll.strpbrk
@ cdecl strrchr(str long) ntdll.strrchr
@ cdecl strspn(str str) ntdll.strspn
@ cdecl strstr(str str) ntdll.strstr
@ cdecl strtod(str ptr) MSVCRT_strtod
@ cdecl strtok(str str) MSVCRT_strtok
@ cdecl strtok_s(ptr str ptr) MSVCRT_strtok_s
@ cdecl strtol(str ptr long) MSVCRT_strtol
@ cdecl strtoul(str ptr long) MSVCRT_strtoul
@ cdecl strxfrm(ptr str long) MSVCRT_strxfrm
@ varargs swprintf(ptr wstr) MSVCRT_swprintf
@ varargs swprintf_s(ptr long wstr) MSVCRT_swprintf_s
@ varargs swscanf(wstr wstr) MSVCRT_swscanf
@ varargs swscanf_s(wstr wstr) MSVCRT_swscanf_s
@ cdecl system(str) MSVCRT_system
@ cdecl tan(double) MSVCRT_tan
@ cdecl tanh(double) MSVCRT_tanh
@ cdecl -arch=x86_64 tanf(float) MSVCRT_tanf
@ cdecl -arch=x86_64 tanhf(float) MSVCRT_tanhf
@ cdecl time(ptr) MSVCRT_time
@ cdecl tmpfile() MSVCRT_tmpfile
# stub tmpfile_s(ptr)
@ cdecl tmpnam(ptr) MSVCRT_tmpnam
# stub tmpnam_s(ptr long)
@ cdecl tolower(long) MSVCRT_tolower
@ cdecl toupper(long) MSVCRT_toupper
@ cdecl towlower(long) ntdll.towlower
@ cdecl towupper(long) ntdll.towupper
@ cdecl ungetc(long ptr) MSVCRT_ungetc
@ cdecl ungetwc(long ptr) MSVCRT_ungetwc
# stub utime
@ cdecl vfprintf(ptr str ptr) MSVCRT_vfprintf
@ cdecl vfprintf_s(ptr str ptr) MSVCRT_vfprintf_s
@ cdecl vfwprintf(ptr wstr ptr) MSVCRT_vfwprintf
@ cdecl vfwprintf_s(ptr wstr ptr) MSVCRT_vfwprintf_s
@ cdecl vprintf(str ptr) MSVCRT_vprintf
@ cdecl vprintf_s(str ptr) MSVCRT_vprintf_s
@ cdecl vsnprintf(ptr long str ptr) MSVCRT_vsnprintf
@ cdecl vsprintf(ptr str ptr) MSVCRT_vsprintf
@ cdecl vsprintf_s(ptr long str ptr) MSVCRT_vsprintf_s
@ cdecl vswprintf(ptr wstr ptr) MSVCRT_vswprintf
@ cdecl vswprintf_s(ptr long wstr ptr) MSVCRT_vswprintf_s
@ cdecl vwprintf(wstr ptr) MSVCRT_vwprintf
@ cdecl vwprintf_s(wstr ptr) MSVCRT_vwprintf_s
# stub wcrtomb(ptr long ptr)
# stub wcrtomb_s(ptr ptr long long ptr)
@ cdecl wcscat(wstr wstr) ntdll.wcscat
@ cdecl wcscat_s(wstr long wstr) MSVCRT_wcscat_s
@ cdecl wcschr(wstr long) ntdll.wcschr
@ cdecl wcscmp(wstr wstr) ntdll.wcscmp
@ cdecl wcscoll(wstr wstr) MSVCRT_wcscoll
@ cdecl wcscpy(ptr wstr) ntdll.wcscpy
@ cdecl wcscpy_s(ptr long wstr) MSVCRT_wcscpy_s
@ cdecl wcscspn(wstr wstr) ntdll.wcscspn
@ cdecl wcsftime(ptr long wstr ptr) MSVCRT_wcsftime
@ cdecl wcslen(wstr) ntdll.wcslen
@ cdecl wcsncat(wstr wstr long) ntdll.wcsncat
@ cdecl wcsncat_s(wstr long wstr long) MSVCRT_wcsncat_s
@ cdecl wcsncmp(wstr wstr long) ntdll.wcsncmp
@ cdecl wcsncpy(ptr wstr long) ntdll.wcsncpy
@ cdecl wcsncpy_s(ptr long wstr long) MSVCRT_wcsncpy_s
@ cdecl wcsnlen(wstr long) MSVCRT_wcsnlen
@ cdecl wcspbrk(wstr wstr) MSVCRT_wcspbrk
@ cdecl wcsrchr(wstr long) ntdll.wcsrchr
@ cdecl wcsrtombs(ptr ptr long ptr) MSVCRT_wcsrtombs
@ cdecl wcsrtombs_s(ptr ptr long ptr long ptr) MSVCRT_wcsrtombs_s
@ cdecl wcsspn(wstr wstr) ntdll.wcsspn
@ cdecl wcsstr(wstr wstr) ntdll.wcsstr
@ cdecl wcstod(wstr ptr) MSVCRT_wcstod
@ cdecl wcstok(wstr wstr) MSVCRT_wcstok
@ cdecl wcstok_s(ptr wstr ptr)
@ cdecl wcstol(wstr ptr long) ntdll.wcstol
@ cdecl wcstombs(ptr ptr long) MSVCRT_wcstombs
@ cdecl wcstombs_s(ptr ptr long wstr long) MSVCRT_wcstombs_s
@ cdecl wcstoul(wstr ptr long) ntdll.wcstoul
@ stub wcsxfrm(ptr wstr long)
@ cdecl wctob(long) MSVCRT_wctob
@ cdecl wctomb(ptr long) MSVCRT_wctomb
# stub wctomb_s(ptr ptr long long)
@ varargs wprintf(wstr) MSVCRT_wprintf
@ varargs wprintf_s(wstr) MSVCRT_wprintf_s
@ varargs wscanf(wstr) MSVCRT_wscanf
@ varargs wscanf_s(wstr) MSVCRT_wscanf_s

# Functions not exported in native dll:
@ cdecl ___mb_cur_max_l_func(ptr)
@ cdecl -arch=i386 __control87_2(long long ptr ptr)
@ cdecl _configthreadlocale(long)
@ cdecl _create_locale(long str) MSVCRT__create_locale
@ cdecl _dupenv_s(ptr ptr str)
@ cdecl _free_locale(ptr) MSVCRT__free_locale
@ cdecl _get_invalid_parameter_handler()
@ cdecl _set_abort_behavior(long long) MSVCRT__set_abort_behavior
@ cdecl _set_invalid_parameter_handler(ptr)
@ cdecl _set_purecall_handler(ptr)
@ cdecl _set_security_error_handler(ptr)
@ cdecl -arch=i386 _statusfp2(ptr ptr)
@ cdecl _wcstod_l(wstr ptr) MSVCRT__wcstod_l
@ cdecl _wdupenv_s(ptr ptr wstr)
@ cdecl _get_printf_count_output()
@ cdecl _set_printf_count_output(long)
