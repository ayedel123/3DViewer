//
// Created by Turnip Sharee on 2/7/24.
//

#ifndef C8_3DVIEWER_V1_0_1_SAVINGFILE_H
#define C8_3DVIEWER_V1_0_1_SAVINGFILE_H

#include <QtCore/QSettings>

class SavingFile {
  QSettings settings;

 public:
  //
  //        savingFile() {
  //            settings = new QSettings("BEBRA", "3DView");
  //        }

  enum Key {
    RotateParams,
    ScaleParams,
    MoveCores,
    BackgroundColor,
    VerticesColor,
    LinesColor,
    ProjectionType,
    VerticesType,
    IsDotted,
    PathToModel,
    WidthLines,
    VerticesSize,
    Model,
    RotateParamsAngle,
    ParamsWasSaved

  };

  QVariant get(Key);
  void setValue(Key, const QVariant&);

  void clear();
};

#endif  // C8_3DVIEWER_V1_0_1_SAVINGFILE_H
