// Copyright 2018 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PlotTypes.h"

   void PlotTypes::natural(commonProperties *pProperties,long segmentID) {

   pIOpenGLImplementation -> OpenSegment(segmentID,propertyLineColor,propertyLineWeight);

   DataList *pItem = NULL;

   pIDataSet -> peek(pItem,&pItem);

   if ( pItem ) {

      if ( ! ( -DBL_MAX == pItem -> data.x ) ) {
         pIOpenGLImplementation -> NewLine(&pItem -> data);
         pIDataSet -> peek(pItem,&pItem);
      }

      while ( pItem ) {
         if ( -DBL_MAX == pItem -> data.x ) {
            while ( pItem && -DBL_MAX == pItem -> data.x ) 
               pIDataSet -> peek(pItem,&pItem);
            if ( ! pItem ) 
               break;
            pIOpenGLImplementation -> NewLine(&pItem -> data);
         }
         pIOpenGLImplementation -> Vertex(&pItem -> data);
         pIDataSet -> peek(pItem,&pItem);
      }

   }

   pIOpenGLImplementation -> CloseSegment(segmentID,TRUE);

   return;
   }