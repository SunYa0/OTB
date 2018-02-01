/*
 * Copyright (C) 2005-2017 Centre National d'Etudes Spatiales (CNES)
 *
 * This file is part of Orfeo Toolbox
 *
 *     https://www.orfeo-toolbox.org/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef otbWrapperQtWidgetParameterList_h
#define otbWrapperQtWidgetParameterList_h

#include <QtWidgets>
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#  include "otbWrapperQtWidgetParameterBase.h"
#endif //tag=QT4-boost-compatibility


namespace otb
{


namespace Wrapper
{

class AbstractParameterList;

/** \class QtWidgetParameterList
 * \brief
 *
 * \ingroup OTBQtWidget
 */
class OTBQtWidget_EXPORT QtWidgetParameterList : public QtWidgetParameterBase
{
  Q_OBJECT

//
// Public methods.
public:
  QtWidgetParameterList( AbstractParameterList *, QtWidgetModel * );
  ~QtWidgetParameterList() override;

//
// Signals.
signals:
  void NotifyUpdate();

//
// Private methods.
private:
  QtWidgetParameterList( const QtWidgetParameterList & ); // purposely not implemented
  void operator = (const QtWidgetParameterList & ); // purposely not implemented

  void DoCreateWidget() override;

  void DoUpdateGUI() override;

//
// Private attributes.
private:

//
// Private slots.
private slots:
};

} // Wrapper

} // otb

#endif