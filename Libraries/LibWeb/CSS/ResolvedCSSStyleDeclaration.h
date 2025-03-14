/*
 * Copyright (c) 2021-2023, Andreas Kling <andreas@ladybird.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/CSS/CSSStyleDeclaration.h>
#include <LibWeb/CSS/Selector.h>

namespace Web::CSS {

class ResolvedCSSStyleDeclaration final : public CSSStyleDeclaration {
    WEB_PLATFORM_OBJECT(ResolvedCSSStyleDeclaration, CSSStyleDeclaration);
    GC_DECLARE_ALLOCATOR(ResolvedCSSStyleDeclaration);

public:
    [[nodiscard]] static GC::Ref<ResolvedCSSStyleDeclaration> create(DOM::Element&, Optional<Selector::PseudoElement::Type> = {});

    virtual ~ResolvedCSSStyleDeclaration() override = default;

    virtual size_t length() const override;
    virtual String item(size_t index) const override;

    virtual Optional<StyleProperty> property(PropertyID) const override;
    virtual Optional<StyleProperty const&> custom_property(FlyString const& custom_property_name) const override;
    virtual WebIDL::ExceptionOr<void> set_property(PropertyID, StringView css_text, StringView priority) override;
    virtual WebIDL::ExceptionOr<void> set_property(StringView property_name, StringView css_text, StringView priority) override;
    virtual WebIDL::ExceptionOr<String> remove_property(PropertyID) override;
    virtual WebIDL::ExceptionOr<String> remove_property(StringView property_name) override;

    virtual String serialized() const override;
    virtual WebIDL::ExceptionOr<void> set_css_text(StringView) override;

private:
    explicit ResolvedCSSStyleDeclaration(DOM::Element&, Optional<CSS::Selector::PseudoElement::Type>);

    virtual void visit_edges(Cell::Visitor&) override;

    virtual bool computed_flag() const override { return true; }

    RefPtr<CSSStyleValue const> style_value_for_property(Layout::NodeWithStyle const&, PropertyID) const;

    GC::Ref<DOM::Element> m_element;
    Optional<CSS::Selector::PseudoElement::Type> m_pseudo_element;
};

}
