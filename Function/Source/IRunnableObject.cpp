// Copyright 2018 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "Function.h"

  STDMETHODIMP Function::GetRunningClass(CLSID *pcid) {
#ifdef FUNCTION_SAMPLE
  *pcid = CLSID_GSystemFunctioNaterSample;
#else
  *pcid = CLSID_GSystemFunctioNater;
#endif
  return E_UNEXPECTED;
  }

  STDMETHODIMP Function::Run(LPBC) { 
  return S_OK; 
  }

  int __stdcall Function::IsRunning() { 
  return 1; 
  }

  STDMETHODIMP Function::LockRunning(BOOL,BOOL) { 
  return S_OK; 
  }

  STDMETHODIMP Function::SetContainedObject(BOOL) { 
  return S_OK; 
  }

