/*=========================================================================

  Program:   Monteverdi2
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See Copyright.txt for details.

  Monteverdi2 is distributed under the CeCILL licence version 2. See
  Licence_CeCILL_V2-en.txt or
  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt for more details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "mvdLayerStackItemModel.h"


/*****************************************************************************/
/* INCLUDE SECTION                                                           */

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.

//
// System includes (sorted by alphabetic order)

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)

//
// Monteverdi includes (sorted by alphabetic order)

namespace mvd
{
/*
  TRANSLATOR mvd::LayerStackItemModel

  Necessary for lupdate to be aware of C++ namespaces.

  Context comment for translator.
*/


/*****************************************************************************/
/* CONSTANTS                                                                 */

namespace
{
} // end of anonymous namespace.


/*****************************************************************************/
/* STATIC IMPLEMENTATION SECTION                                             */


/*****************************************************************************/
/* CLASS IMPLEMENTATION SECTION                                              */

/*******************************************************************************/
LayerStackItemModel
::LayerStackItemModel( QObject* parent ) :
  QAbstractItemModel( parent )
{
}

/*******************************************************************************/
LayerStackItemModel
::~LayerStackItemModel()
{
}

/*******************************************************************************/
int
LayerStackItemModel
::columnCount( const QModelIndex & parent ) const
{
  return ITEM_ROLE_COUNT;
}

/*******************************************************************************/
QVariant
LayerStackItemModel
::data( const QModelIndex & index, int role ) const
{
  return QVariant();
}

/*******************************************************************************/
QModelIndex
LayerStackItemModel
::index( int row,
         int column,
         const QModelIndex & parent ) const
{
  return QModelIndex();
}

/*******************************************************************************/
QModelIndex
LayerStackItemModel
::parent( const QModelIndex & index ) const
{
  return QModelIndex();
}

/*******************************************************************************/
int
LayerStackItemModel
::rowCount( const QModelIndex & parent ) const
{
  return 0;
}

/*******************************************************************************/
bool
LayerStackItemModel
::setData( const QModelIndex & index,
           const QVariant & value,
           int role )
{
  return false;
}

/*******************************************************************************/
/* SLOTS                                                                       */
/*******************************************************************************/

} // end namespace 'mvd'
