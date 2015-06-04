#ifndef QTRENDERERPLATFORMSUPPORT_H
#define QTRENDERERPLATFORMSUPPORT_H

#include "AbstractRenderer.h"
#include <QRect>

class QtRendererPlatformSupport : public AbstractRendererPlatformSupport
{
public:
  virtual void RenderTextInOpenGL(
      const char *text,
      int x, int y, int w, int h,
      FontInfo font,
      int align_horiz, int align_vert,
      const Vector3d &rgbf);

  virtual int MeasureTextWidth(const char *text, FontInfo font);

  virtual void LoadTexture(const char *url, GLuint &texture_id, Vector2ui &tex_size);

protected:
  QRect WorldRectangleToPixelRectangle(const QRect &world);
};

#endif // QTRENDERERPLATFORMSUPPORT_H
