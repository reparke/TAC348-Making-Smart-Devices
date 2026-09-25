---
title: Pre-Lecture Videos and Readings
layout: single
category: Readings
description: "Weekly preparation videos and readings for TAC 348 Making Smart Devices, a project-based physical computing course at USC."
toc: true
toc_label: "Quick Links"
toc_icon: "bookmark"  # corresponding Font Awesome icon name (without fa prefix)
toc_sticky: true

---


{% capture dates_string %}
  {% include /functions/calc_week_dates.html %}
{% endcapture %}
{% assign dates_array = dates_string | split: '::' %}	

{% assign has_spring_break = site.calendar.semester_has_spring_break %}
{% assign week_num_spring_break = site.calendar.semester_week_of_spring_break %}

<p><i>To be completed prior to coming to lecture in a given week</i></p>

{% assign all_readings = site.readings | group_by: 'week' %}
{% for week in all_readings %}
{% assign index = week.name | times: 1 %} 
{% assign current_dates = dates_array[index] | split: '|' %}
{% comment %}
  This if block prints "Spring Break" before printing the instruction week which
    comes after the week of Spring Break (according to the calendar)
{% endcomment %}
{% if has_spring_break == true and index == week_num_spring_break %}
<ul><li>Spring Break</li></ul>
{% endif %}

{% if index != 16 %}

<ul>
    {% assign items = week.items | sort: 'order' %}
    {% for item in items %}
    <li><a href="{{ site.baseurl }}{{ item.url }}">Week {{ week.name }}</a> (complete prior to <b>{{current_dates[2] | strip}})</b></li>
    {% endfor %}
</ul>
{% endif %}
{% if index >= 16 %}
<h2 id="#bonus_material">Bonus Material<a class="header-link" href="#bonus_material" title="Permalink"></a></h2>
<ul>
    {% assign items = week.items | sort: 'order' %}
    {% for item in items %}
      {% if item.show_in_list == false %}
        {% continue %}
      {% endif %}    
    <li><a href="{{ site.baseurl }}{{ item.url }}">Extra Videos</a></li>
    {% endfor %}
</ul>
{% endif %}
{% endfor %}

