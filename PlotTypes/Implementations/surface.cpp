// Copyright 2018 InnoVisioNate Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PlotTypes.h"
#include "utils.h"

   void PlotTypes::surface(commonProperties *pProperties,long segmentID) {
   
   DataPoint v[5];
   DataList *dlTemp,*dlNext,*dl;
   DataPoint firstPoint,secondPoint,thirdPoint,fourthPoint;
   int endOfData,kAccross;

   DataPoint xProd0,xProd1,avgNormal[4];

   pIOpenGLImplementation -> BeginSurface(segmentID,propertyTopSurfaceColor,propertyBottomSurfaceColor);
   
   kAccross = 0;
   endOfData = FALSE;
    
   dl = (DataList *)NULL;

   pIDataSet -> get(dl,&firstPoint,&dl);

   pIOpenGLImplementation -> BeginOpenGLMode(GL_QUADS);
      
   while ( dl ) {
         
      dlNext = dl;

      pIDataSet -> get(dlNext,&secondPoint,&dlTemp);

      if ( ! dlTemp ) break;
         
      if ( secondPoint.x != firstPoint.x ) {
         kAccross = 0;
         pIDataSet -> get(dl,&firstPoint,&dl);
         continue;
      }
         
      fourthPoint = secondPoint;
         
      while ( secondPoint.x == firstPoint.x ) {
         pIDataSet -> get(dlNext,&secondPoint,&dlNext);
         if ( ! dlNext ) {
            endOfData = TRUE;
            break;
         }
      }
   
      if ( endOfData ) break;
         
      for ( int j = 0; j < kAccross; j++ ) {
         if ( ! dlNext ) {
            endOfData = TRUE;
            break;
         }
         pIDataSet -> get(dlNext,&secondPoint,&dlNext);
      }
   
      if ( endOfData ) break;
    
      pIDataSet -> get(dlNext,&thirdPoint,&dlTemp);
         
      v[0] = firstPoint;
      v[1] = secondPoint;
      v[2] = thirdPoint;
      v[3] = fourthPoint;
   
      // x-product of the vector from 0->1 with 0->3

      VminusV(&v[1],&v[0],&xProd0);
      VminusV(&v[3],&v[0],&xProd1);

      VxV(&xProd0,&xProd1,&avgNormal[0]);
      unitVector(&avgNormal[0],&avgNormal[0]);
    
      // x-product of the vector from 1->2 with 1->0

      VminusV(&v[2],&v[1],&xProd0);
      VminusV(&v[0],&v[1],&xProd1);

      VxV(&xProd0,&xProd1,&avgNormal[1]);
      unitVector(&avgNormal[1],&avgNormal[1]);

      // x-product of the vector from 2->3 with 2->1

      VminusV(&v[3],&v[2],&xProd0);
      VminusV(&v[1],&v[2],&xProd1);

      VxV(&xProd0,&xProd1,&avgNormal[2]);
      unitVector(&avgNormal[2],&avgNormal[2]);
    
      // x-product of the vector from 3->0 with 3->2

      VminusV(&v[0],&v[3],&xProd0);
      VminusV(&v[2],&v[3],&xProd1);

      VxV(&xProd0,&xProd1,&avgNormal[3]);
      unitVector(&avgNormal[3],&avgNormal[3]);

      //pIOpenGLImplementation -> Normal3dv(avgNormal[4]);

      for ( int vk = 0; vk < 4; vk++ ) {
         pIOpenGLImplementation -> Vertex(&v[vk]);
         VplusV(&v[vk],&avgNormal[vk],&avgNormal[vk]);
         pIOpenGLImplementation -> NormalDp(&avgNormal[vk]);
      }

      kAccross++;
   
      pIDataSet -> get(dl,&firstPoint,&dl);
    
   }

   pIOpenGLImplementation -> CloseSegment(segmentID,TRUE);   

   return;
   }
