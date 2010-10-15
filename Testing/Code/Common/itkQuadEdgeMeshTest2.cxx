/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkQuadEdgeMeshTest2.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "itkQuadEdgeMesh.h"

int itkQuadEdgeMeshTest2( int , char* [] )
{
  std::cout << "Testing points and simple edges... " << std::ends;

  typedef double                                   PixelType;
  typedef itk::QuadEdgeMesh< PixelType, 3 >        MeshType;
  typedef MeshType::CellType                       CellType;
  typedef itk::QuadEdgeMeshLineCell< CellType >    LineType;
  typedef LineType::QEType                         QuadEdgeType;
  typedef CellType::CellAutoPointer                CellAutoPointer;

  MeshType::Pointer  mesh = MeshType::New();

  MeshType::PointType p0;
  MeshType::PointType p1;
  MeshType::PointType p2;

  p0[ 0 ] = -1.0; p0[ 1 ] = 0.0; p0[ 2 ] = 0.0;
  p1[ 0 ] =  1.0; p1[ 1 ] = 0.0; p1[ 2 ] = 0.0;
  p2[ 0 ] =  1.0; p2[ 1 ] = 1.0; p2[ 2 ] = 0.0;

  mesh->SetPoint( 0, p0 );
  mesh->SetPoint( 1, p1 );
  mesh->SetPoint( 2, p2 );

  CellAutoPointer line0;
  line0.TakeOwnership( new LineType );
  line0->SetPointId( 0, 0 );
  line0->SetPointId( 1, 1 );
  mesh->SetCell( 0, line0 );

  CellAutoPointer line1;
  line1.TakeOwnership( new LineType );
  line1->SetPointId( 0, 1 );
  line1->SetPointId( 1, 2 );
  mesh->SetCell( 1, line1 );

  CellAutoPointer line2;
  line2.TakeOwnership( new LineType );
  line2->SetPointId( 0, 2 );
  line2->SetPointId( 1, 0 );
  mesh->SetCell( 2, line2 );

  if( mesh->GetNumberOfPoints() != 3 )
    {
    std::cout << "Not all points added." << std::endl;
    return EXIT_FAILURE;
    }

  if( ( mesh->GetNumberOfCells( ) != 0 )
   && ( mesh->GetNumberOfEdges( ) != 3 ) )
    {
    std::cout << "Not all cells added." << std::endl;
    return EXIT_FAILURE;
    }

  typedef MeshType::CellsContainer::Iterator CellIterator;
  CellIterator cellIterator = mesh->GetCells()->Begin();
  unsigned int ids[ ] = { 0, 1, 2, 1, 2, 0, 2, 0, 1 };
  int itIds = 0;

  while( cellIterator != mesh->GetCells()->End() )
    {
    MeshType::CellType* cellptr = cellIterator.Value();
    LineType* lineCell = dynamic_cast< LineType* >( cellptr );
    lineCell->GetNameOfClass();
    QuadEdgeType* QEGeom = lineCell->GetQEGeom( );
    QuadEdgeType::IteratorGeom git = QEGeom->BeginGeomLnext();
    while( git != QEGeom->EndGeomLnext() )
      {
      if( ids[ itIds ] != *git )
        {
        std::cout << "Problem with splicing edges." << std::endl;
        return EXIT_FAILURE;
        }
      itIds++;
      git++;
      }
    cellIterator++;
    }

  std::cout << "done!" << std::endl;
  return EXIT_SUCCESS;
}