---
title: Assignments
layout: single
category: assignments
classes: wide
---


<ul>
{% assign all_assignments = site.assignments | sort: "number" %}
{% for week in all_assignments %}
   {% if week.show_in_list == false %}
   {% continue %}
   {% endif %}
  <li>
  	<a href="{{ site.baseurl }}{{ week.url }}">#{{ week.number}} - {{ week.title }}</a> 
  	(Due: <b>{{ week.date_due }}</b>)</li>
{% endfor %}
</ul>




