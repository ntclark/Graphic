// Copyright 2018 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ViewSet.h"

  ViewSet::_IEnumConnectionPoints::_IEnumConnectionPoints(ViewSet *pp,_IConnectionPoint **cp,int connectionPointCount) : 
   	  cpCount(connectionPointCount),
        pParent(pp) {
 
  connectionPoints = new _IConnectionPoint *[cpCount];
  for ( int k = 0; k < cpCount; k++ ) {
     connectionPoints[k] = cp[k];
     connectionPoints[k] -> AddRef();
  }

  Reset();
  return;
  };


  ViewSet::_IEnumConnectionPoints::~_IEnumConnectionPoints() { 
  for ( int k = 0; k < cpCount; k++ )
     connectionPoints[k] -> Release();
  delete [] connectionPoints;
  return;
  };



  HRESULT ViewSet::_IEnumConnectionPoints::QueryInterface(REFIID riid,void **ppv) {
  *ppv = NULL;
  if ( IID_IUnknown != riid && IID_IEnumConnectionPoints != riid ) return E_NOINTERFACE;
  *ppv = (void *)(this);
  AddRef();
  return S_OK;
  }


  unsigned long __stdcall ViewSet::_IEnumConnectionPoints::AddRef() {
  return pParent -> AddRef();
  }

  unsigned long __stdcall ViewSet::_IEnumConnectionPoints::Release() {
  return pParent -> Release();
  }


  HRESULT ViewSet::_IEnumConnectionPoints::Next(ULONG countRequested,IConnectionPoint **rgpcn,ULONG *pcFetched) {
  ULONG found;

  if ( !rgpcn ) return E_POINTER;

  if ( *rgpcn && enumeratorIndex < cpCount ) {
     if ( pcFetched ) 
       *pcFetched = 0L;
     else
       if ( countRequested != 1L ) return E_POINTER;
  }
  else return S_FALSE;

  for ( found = 0; enumeratorIndex < cpCount && countRequested > 0; enumeratorIndex++, rgpcn++, found++, countRequested-- ) {
    *rgpcn = connectionPoints[enumeratorIndex];
    if ( *rgpcn ) (*rgpcn) -> AddRef();
  }

  if ( pcFetched ) *pcFetched = found;

  return S_OK;
  }


  HRESULT ViewSet::_IEnumConnectionPoints::Skip(ULONG cSkip) {
  if ( cpCount < 1 || ((enumeratorIndex + (int)cSkip) < cpCount) ) return S_FALSE;
  enumeratorIndex += cSkip;
  return S_OK;
  }


  HRESULT ViewSet::_IEnumConnectionPoints::Reset() {
  enumeratorIndex = 0;
  return S_OK;
  }

  HRESULT ViewSet::_IEnumConnectionPoints::Clone(IEnumConnectionPoints **ppEnum) {
  _IEnumConnectionPoints* p;

  *ppEnum = NULL;

  p = new _IEnumConnectionPoints(pParent,connectionPoints,cpCount);
  p -> enumeratorIndex = enumeratorIndex;
  p -> QueryInterface(IID_IEnumConnectionPoints,(void **)ppEnum);

  return S_OK;
  }

