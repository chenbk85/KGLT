#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>
#include <tr1/memory>
#include "../kazbase/unicode.h"

namespace kglt {
namespace ui {

class ElementImpl;

class Element {
public:
    Element(std::shared_ptr<ElementImpl> impl);

    void text(const unicode& content);
    const unicode text() const;

    void add_class(const std::string& cl);

    std::string css(const std::string& property);
    void css(const std::string& property, const std::string& value);
    void attr(const std::string& property, const std::string& value);

    void show() { css("visibility", "visible"); }
    void hide() { css("visibility", "hidden"); }

    void id(const std::string& id);

    void scroll_to_bottom();
private:
    std::shared_ptr<ElementImpl> impl_;
};

}
}

#endif // ELEMENT_H
