#ifndef OVERLAY_H
#define OVERLAY_H

#include <cstdint>
#include <kazmath/mat4.h>

#include "object.h"

namespace kglt {

/**
  An overlay represents a 2D layer on top of the rendered scene. Unlike other
  objects, overlays can only be a child of the scene node itself.

  You can attach objects to the overlay, but their z position must lie within
  the -1.0 -> 1.0 range.

  The set_ortho() method controls the orthographic projection of the overlay. The
  default is -1.0 (L), 1.0 (R), -1.0 (B), 1.0 (T).

  Overlays are rendered from lowest zindex first to highest.
*/

class Overlay : public Object {
public:
    typedef std::tr1::shared_ptr<Overlay> ptr;

    Overlay();

    void set_zindex(int32_t zindex) { zindex_ = zindex; }
    int32_t zindex() const { return zindex_; }

    void set_ortho(double left, double right, double bottom, double top);
    const kmMat4& projection_matrix() const { return projection_matrix_; }

    void accept(ObjectVisitor& visitor) {
        do_accept<Overlay>(this, visitor);
    }
private:
    int32_t zindex_;
    kmMat4 projection_matrix_;

    bool can_set_parent(Object* p);
};

}
#endif // OVERLAY_H