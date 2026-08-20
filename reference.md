---
title: Reference
category: reference
layout: single
classes: wide

---


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





