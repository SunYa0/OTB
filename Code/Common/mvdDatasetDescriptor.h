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

#ifndef __mvdDatasetDescriptor_h
#define __mvdDatasetDescriptor_h

//
// Configuration include.
//// Included at first position before any other ones.
#include "ConfigureMonteverdi2.h"


/*****************************************************************************/
/* INCLUDE SECTION                                                           */

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.
#include <QtXml>

//
// System includes (sorted by alphabetic order)

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)

//
// Monteverdi includes (sorted by alphabetic order)
#include "mvdAbstractModel.h"


/*****************************************************************************/
/* PRE-DECLARATION SECTION                                                   */

//
// External classes pre-declaration.
namespace
{
}

namespace mvd
{
//
// Internal classes pre-declaration.
class AbstractImageModel;

/*****************************************************************************/
/* CLASS DEFINITION SECTION                                                  */

/**
 * \class DatasetDescriptor.
 *
 * \brief WIP.
 */
class Monteverdi2_EXPORT DatasetDescriptor :
    public AbstractModel
{

  /*-[ QOBJECT SECTION ]-----------------------------------------------------*/

  Q_OBJECT;

  /*-[ PUBLIC SECTION ]------------------------------------------------------*/

//
// Public types.
public:
  /**
   * \class BuildContext
   * \brief WIP.
   */
  class BuildContext
  {
    //
    // Public methods.
  public:
    BuildContext( const QString& filename ) :
      m_Filename( filename )
    {
    }

    //
    // Public attributes
  public:
    QString m_Filename;
  };

//
// Public methods.
public:

  /** \brief Constructor. */
  DatasetDescriptor( QObject* parent =NULL );

  /** \brief Destructor. */
  virtual ~DatasetDescriptor();

  /**
   */
  void InsertImageModel( int id,
			 const QString& imageFilename,
			 void* imageSettings,
			 const QString& quicklookFilename );

  /**
   */
  inline QDomElement FirstImageElement();

  /**
   */
  static
    inline QDomElement NextImageSiblingElement( const QDomElement& sibling );

  /**
   */
  static
    void GetImageModel( const QDomElement& imageSibling,
			int& id,
			QString& filename,
			void* settings,
			QString& quicklookFilename );

  /**
   */
  void Write( const QString& filename ) const;

  /*-[ SIGNALS SECTION ]-----------------------------------------------------*/

//
// Signals.
signals:

  /*-[ PROTECTED SECTION ]---------------------------------------------------*/

//
// Protected methods.
protected:

  //
  // AbstractModel overrides.

  /** */
  virtual void virtual_BuildModel( void* context =NULL );

//
// Protected attributes.
protected:

  /*-[ PRIVATE SECTION ]-----------------------------------------------------*/

//
// Private methods.
private:

  /**
   * \brief Serialize an STL-compliant container to a QDomElement
   */
  template< typename TInputIterator >
  inline
  QDomElement CreateContainerNode( const TInputIterator& first,
				   const TInputIterator& last,
                                   const QString& tagName );

  /**
   */
  void Read( const QString& filename );

  /**
   */
  void Read( QIODevice* device );

  /**
   */
  void Write( QIODevice& device ) const;

//
// Private attributes.
private:

  /**
   */
  enum Element
  {
    ELEMENT_DOCUMENT_ROOT =0,
    ELEMENT_IMAGE_GROUP,
    ELEMENT_IMAGE,
    ELEMENT_QUICKLOOK,
    ELEMENT_SETTINGS_GROUP,
    ELEMENT_RGB_CHANNELS,
    ELEMENT_DYNAMICS_PARAMETERS,

    ELEMENT_COUNT
  };

  /**
   */
  static const char* TAG_NAMES[ ELEMENT_COUNT ];

  /**
   */
  QDomDocument m_DomDocument;

  /**
   */
  QDomElement m_DatasetElement;


  /*-[ PRIVATE SLOTS SECTION ]-----------------------------------------------*/

//
// Slots.
private slots:
};

} // end namespace 'mvd'

/*****************************************************************************/
/* INLINE SECTION                                                            */

//
// Monteverdi deferred includes (sorted by alphabetic order)
#include "mvdDatasetModel.h"

namespace mvd
{

/*****************************************************************************/

/*****************************************************************************/
inline
QDomElement
DatasetDescriptor
::FirstImageElement()
{
  return m_DatasetElement.firstChildElement( "image" );
}

/*****************************************************************************/
inline
QDomElement
DatasetDescriptor
::NextImageSiblingElement( const QDomElement& sibling )
{
  return sibling.nextSiblingElement( "image" );
}

/*****************************************************************************/
template< typename TInputIterator >
inline
QDomElement
DatasetDescriptor
::CreateContainerNode( const TInputIterator& first,
		       const TInputIterator& last,
		       const QString& tagName )
{
  QStringList stringList;

  for( TInputIterator it( first );
       it != last;
       ++ it )
    {
    stringList.append( QString( "%1" ).arg( *it ) );
    }

  QDomText textNode( m_DomDocument.createTextNode( stringList.join( " " ) ) );
  assert( !textNode.isNull() );

  QDomElement vectorElement( m_DomDocument.createElement( tagName ) );
  assert( !vectorElement.isNull() );

  vectorElement.appendChild( textNode );

  return vectorElement;
}

} // end namespace 'mvd'

#endif // __mvdDatasetDescriptor_h
