---
title: Reference
category: reference
layout: single
classes: wide
description: "Illustrated wiring, component, sensor, motor, and embedded-programming reference guides for physical computing students and educators."

---

These course-produced technical guides cover components, wiring, and embedded programming while building and debugging projects. For external documentation, tools, books, and project ideas, see [Resources](/resources).


<ul>
{% assign all_reference = site.reference | sort: "title" %}
{% for ref in all_reference %}
   {% if ref.show_in_list == false %}
   {% continue %}
   {% endif %}
  <li>
  	<a href="{{ site.baseurl }}{{ ref.url }}">{{ ref.title }}</a> 
  </li>
{% endfor %}
</ul>





