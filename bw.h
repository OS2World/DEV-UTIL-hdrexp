//OS/2 fan-out includefile for BIF/Window

#ifndef __BIFWIN_WAS_HERE__     
// optimize out of duplicatede inclusion of approx. 2Mb headerfiles :-(
#  define __BIFWIN_WAS_HERE__
#  define INCL_DOSMODULEMGR
#  define INCL_WIN
#  include <os2.h>
#endif


#ifdef BIFINCL_WINALL
// The programmer is lazy...
#  define BIFINCL_FRAME
#  define BIFINCL_APPWND
#  define BIFINCL_DIALOG
#  define BIFINCL_COMMONHANDLERS
#  define BIFINCL_FRAMEHANDLERS
#  define BIFINCL_CLIENTHANDLERS
#  define BIFINCL_MOUSEHANDLERS
#  define BIFINCL_ADVANCEDHANDLERS
#  define BIFINCL_OWNERDRAWHANDLERS
#  define BIFINCL_CONTROLS
#  define BIFINCL_MODULE
#  define BIFINCL_APPLICATION
#  define BIFINCL_PAINT
#  define BIFINCL_MESSAGEBOX
#endif

//dependencies
#ifdef BIFINCL_APPWND
#  define BIFINCL_FRAME
#  define BIFINCL_COMMONHANDLERS
#endif
#ifdef BIFINCL_DIALOG
#  define BIFINCL_FRAME
#  define BIFINCL_COMMONHANDLERS
#endif
#ifdef BIFINCL_APPLICATION
#  define BIFINCL_MODULE
#endif

//include core&misc unconditionally:
#if !defined(__BW_CORE_H_INCLUDED)
#  include <os2\bw_core.h>
#endif
#if !defined(__BW_MISC_H_INCLUDED)
#  include <os2\bw_misc.h>
#endif


//fan-out include (with optimization):

#if defined(BIFINCL_COMMONHANDLERS) && !defined(__BW_COMH_H_INCLUDED)
#  include <os2\bw_comh.h>
#endif

#if defined(BIFINCL_FRAME) && !defined(__BW_FRAME_H_INCLUDED)
#  include <os2\bw_frame.h>
#endif
#if defined(BIFINCL_APPWND) && !defined(__BW_APPW_H_INCLUDED)
#  include <os2\bw_appw.h>
#endif
#ifdef BIFINCL_DIALOG
// bw_dlg.h fans out, can't optimze here
#  include <os2\bw_dlg.h>
#endif

#ifdef BIFINCL_FRAMEHANDLERS
#  include <os2\bw_fh.h>
#endif
#ifdef BIFINCL_CLIENTHANDLERS
#  include <os2\bw_ch.h>
#endif
#ifdef BIFINCL_MOUSEHANDLERS
#  include <os2\bw_mouse.h>
#endif
#ifdef BIFINCL_ADVANCEDHANDLERS
#  include <os2\bw_ah.h>
#endif
#ifdef BIFINCL_OWNERDRAWHANDLERS
#  include <os2\bw_odh.h>
#endif

#ifdef BIFINCL_CONTROLS
// bw_ctl.h fans out, can't optimze here
#  include <os2\bw_ctl.h>
#endif

#if defined(BIFINCL_MODULE) && !defined(__BW_MODUL_H_INCLUDED)
#  include <os2\bw_modul.h>
#endif

#if defined(BIFINCL_APPLICATION) && !defined(__BW_APP_H_INCLUDED)
#  include <os2\bw_app.h>
#endif

#ifdef BIFINCL_PAINT
#  include <os2\bw_paint.h>
#endif

#if defined(BIFINCL_MESSAGEBOX) && !defined(__BW_MSGBX_H_INCLUDED)
#  include <os2\bw_msgbx.h>
#endif

