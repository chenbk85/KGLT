#include <Rocket/Core/Element.h>
#include <Rocket/Core/ElementText.h>
#include <Rocket/Core/ElementDocument.h>

#include "interface.h"
#include "ui_private.h"

namespace kglt {
namespace ui {


Element::Element(std::shared_ptr<ElementImpl> impl):
    impl_(impl) {

}

void Element::text(const unicode& text) {
    impl_->set_text(text);
}

const unicode Element::text() const {
    return impl_->text();
}

void Element::add_class(const std::string& cl) {
    impl_->add_class(cl);
}

std::string Element::css(const std::string& property) {
    return impl_->css(property);
}

void Element::css(const std::string& property, const std::string& value) {
    impl_->css(property, value);
}

void Element::attr(const std::string& property, const std::string& value) {
    impl_->attr(property, value);
}

void Element::id(const std::string& id) {
    impl_->id(id);
}

void Element::scroll_to_bottom() {
    impl_->scroll_to_bottom();
}

}

}
