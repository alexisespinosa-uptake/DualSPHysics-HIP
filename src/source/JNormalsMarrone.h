//HEAD_DSPH
/*
 <DUALSPHYSICS>  Copyright (c) 2020 by Dr Jose M. Dominguez et al. (see http://dual.sphysics.org/index.php/developers/). 

 EPHYSLAB Environmental Physics Laboratory, Universidade de Vigo, Ourense, Spain.
 School of Mechanical, Aerospace and Civil Engineering, University of Manchester, Manchester, U.K.

 This file is part of DualSPHysics. 

 DualSPHysics is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License 
 as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.
 
 DualSPHysics is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details. 

 You should have received a copy of the GNU Lesser General Public License along with DualSPHysics. If not, see <http://www.gnu.org/licenses/>. 
*/

/// \file JNormalsMarrone.h \brief Declares the class \ref JNormalsMarrone.

#ifndef _JNormalsMarrone_
#define _JNormalsMarrone_

//:#############################################################################
//:# Cambios:
//:# =========
//:# - Clase para calcular normales para Marrone BC a partir de informacion de 
//:#   normales generada por GenCase. (07-04-2019)
//:# - Mejora el calculo de normales para casos 3D con angulos rectos. (05-06-2019)
//:# - Genera excepcion cuando no hay datos de normales en el fichero NBI4. (07-08-2019)
//:# - Cambia uso de JFormatFiles2 por JVtkLib. (12-12-2019)
//:# - Usa macro para lanzar excepciones. (12-12-2019)
//:# - Se corrigio un error calculando la normal cuando habia varias opciones 
//:#   a la misma distancia. (01-02-2020)
//:# - Se establece un directorio de salida DirOut independiente del de entrada. (29-03-2020)
//:# - Se corrigio un error calculando la normal cuando habia varias opciones 
//:#   a la misma distancia buscando punto de interseccion mas cercano. (02-04-2020)
//:# - Se descartan las normales calculadas por proyeccion que sean mayores que 1.5 Dist. (22-07-2021)
//:#############################################################################

#include "JObject.h"
#include "TypesDef.h"
#include <string>
#include <climits>
#include <vector>


//##############################################################################
//# JNormalsMarrone
//##############################################################################
/// \brief Code to compute Marrone normals according data normals generated by GenCase.

class JNormalsMarrone : protected JObject
{
protected:
  std::string CaseDir;
  std::string CaseName;
  std::string DirOut;

  bool ExternalData;

  //-Particle data.
  bool Data2D;           ///<Indicates 2D data.
  double Data2DPosY;     ///<Y value in 2D data.
  double H;
  double Dp;
  unsigned SizePart;
  tdouble3 *PartPos;
  tdouble3 *PartNor;

  //-Normal data.
  double Dist;           ///<Distance used for calculating normal data (tipically KernelSize).
  unsigned SizeNor;
  unsigned *NormalBegin; ///<Normals for each particle [SizePart+1]
  tdouble3 *Normals;     ///<Unitary normal to shape [SizeNor]
  double   *NormalsDist; ///<Distance to shape [SizeNor]
  tdouble3 *OutVecs;     ///<Vector to limit of shape [SizeNor]
  double   *OutVecsDist; ///<Distance to limit of shape [SizeNor]

  void ResetParts();
  void ResetNormals();
  void AllocParts(unsigned size);
  void AllocNormals(unsigned size);
  void LoadBoundParticles();
  void LoadNormalData();
  void SaveVtkNormalData();
  unsigned MaxNormalsByPart()const;
  void ComputeNormalsMarrone();
  void SaveVtkNormalFinal(std::string file);
public:
  JNormalsMarrone();
  ~JNormalsMarrone();
  void Reset();

  static std::string GetNormalDataFile(std::string casename);
  void RunCase(std::string casename,std::string dirout,bool savevtk);
  void RunData(std::string casename,std::string dirout,bool savevtk
    ,bool data2d,double data2dposy,double h,double dp,unsigned sizepart,tdouble3 *partpos
    ,double dist,unsigned sizenor,unsigned *norbegin,tdouble3 *normals,double *normalsdist
    ,tdouble3 *outvecs,double *outvecsdist,tdouble3 *partnor);

  const tdouble3* GetPartNor()const{ return(PartNor); }
  unsigned GetPartNorSize()const{ return(SizePart); }

};

#endif

