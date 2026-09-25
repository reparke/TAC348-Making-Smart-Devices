---
title: Weekly Schedule
layout: single
description: "Week-by-week schedule of lectures, projects, exercises, and preparation for TAC 348 Making Smart Devices at USC."
toc: true
toc_label: "Quick Links"
toc_icon: "bookmark"  # corresponding Font Awesome icon name (without fa prefix)
toc_sticky: true
---

{% capture dates_string %}
  {% include /functions/calc_week_dates.html %}
{% endcapture %}
{% assign dates_array = dates_string | split: '::'%}	
{% for week in dates_array %}
  {% assign elements = week | split: '|' %}
  {% assign week.end = elements[0] %}
{% endfor %}

{% assign has_spring_break = site.calendar.semester_has_spring_break %}
{% assign week_num_spring_break = site.calendar.semester_week_of_spring_break %}

{% assign readings = site.readings | sort: "number" %}
{% assign lectures = site.lectures | sort: "number" %}
{% assign assignments = site.assignments | sort: "number" %}
{% assign all_items = lectures | concat: readings | concat: assignments | group_by: 'week'  %}

{% for week in all_items %}
  {% comment %}
    Capture stores strings so convert to int to use in array
    {% endcomment %}
  {% assign index = week.name | times: 1 %} 

  {% assign current_dates = dates_array[index] | split: '|' %}
  {% comment %} 
    This if block prints "Spring Break" before printing the instruction week which
    comes after the week of Spring Break (according to the calendar)
    {% endcomment %}
  {% if has_spring_break == true and index == week_num_spring_break %}
  <h2 id="spring_break">Spring Break
  <a class="header-link" href="#spring_break" title="Permalink"></a></h2>
  {% endif %}
  
  {% if index != 16 %}

  <h2 id="week_{{ week.name }}">Week {{ week.name }} ({{current_dates[2] | strip}} - {{current_dates[3] | strip}})
  <a class="header-link" href="#week_{{ week.name }}" title="Permalink"></a></h2>
  <div class="weekly_schedule_content_area">
    <h3 class="no_toc weekly_schedule_content_label">Readings / Videos / Pre-Lecture Activities</h3>
    <ul>
      {% assign content_items = week.items %}
      {% for item in content_items %}
        {% if item.category == "readings" %}
          <li class="weekly_schedule_content_item">
            <a href="{{ site.baseurl }}{{ item.url }}">Pre-Lecture Activities</a> (complete prior to <b>{{current_dates[2] | strip}})</b>
          </li>
        {% endif %}
      {% endfor %}
    </ul>
  </div>
  <div class="weekly_schedule_content_area">
    <h3 class="no_toc weekly_schedule_content_label">Lectures</h3>
    <ul>
      {% assign content_items = week.items %}
      {% for item in content_items %}
        {% if item.category == "lectures" %}
          {% if item.show_in_list == false %}
            {% continue %}
          {% endif %}
          <li class="weekly_schedule_content_item">
            <a href="{{ site.baseurl }}{{ item.url }}">{{ item.title }}</a>
          </li>
        {% endif %}
      {% endfor %}
    </ul>
  </div>
  <div class="weekly_schedule_content_area">
    <h3 class="no_toc weekly_schedule_content_label">Assignments</h3>
    <p><i>Due the following week</i></p>
    <ul>
      {% assign content_items = week.items %}
      {% for item in content_items %}
         {% if item.show_in_list == false %}
   			{% continue %}
         {% endif %}
        {% if item.category == "assignments" %}
          <li class="weekly_schedule_content_item">
            <a href="{{ site.baseurl }}{{ item.url }}">#{{ item.number}} - {{ item.title }}</a> 
          (Due: <b>{{ item.date_due }}</b>)
          </li>    
        {% endif %}
      {% endfor %}
    </ul>
  </div>
  {% endif %}
{% endfor %}

{% comment %}
It is inefficient to have identical for loops (one for current semester content and one for bonus material. 
Consider revising and possibly using Liquid sort function
{% endcomment %}

{% for week in all_items %}
  {% comment %}
    Capture stores strings so convert to int to use in array
  {% endcomment %}
  {% assign index = week.name | times: 1 %} 

  {% assign current_dates = dates_array[index] | split: '|' %}
  {% if index == 16 %}
  <h2 id="#bonus_material">Bonus Material<a class="header-link" href="#bonus_material" title="Permalink"></a></h2>
  <div class="weekly_schedule_content_area">
    <h3 class="no_toc weekly_schedule_content_label">Pre-Lecture Activities / Reading / Video</h3>
    <ul>
      {% assign content_items = week.items %}
      {% for item in content_items %}
        {% if item.category == "reading" %}
          <li class="weekly_schedule_content_item">
            <a href="{{ site.baseurl }}{{ item.url }}">Pre-Lecture Activities</a> (complete prior to <b>{{current_dates[2] | strip}})</b>
          </li>
        {% endif %}
      {% endfor %}
    </ul>
  </div>
  <div class="weekly_schedule_content_area">
    <h3 class="no_toc weekly_schedule_content_label">Lectures</h3>
    <ul>
      {% assign content_items = week.items %}
      {% for item in content_items %}
        {% if item.category == "lectures" %}
          {% if item.show_in_list == false %}
            {% continue %}
          {% endif %}        
          <li class="weekly_schedule_content_item">
            <a href="{{ site.baseurl }}{{ item.url }}">{{ item.title }}</a>
          </li>
        {% endif %}
      {% endfor %}
    </ul>
  </div>
  <div class="weekly_schedule_content_area">
    <h3 class="no_toc weekly_schedule_content_label">Assignments</h3>
    <ul>
      {% assign content_items = week.items %}
      {% for item in content_items %}
         {% if item.show_in_list == false %}
   			{% continue %}
         {% endif %}
        {% if item.category == "assignments" %}
          <li class="weekly_schedule_content_item">
            <a href="{{ site.baseurl }}{{ item.url }}">#{{ item.number}} - {{ item.title }}</a> 
          (Due: <b>{{ item.date_due }}</b>)
          </li>    
        {% endif %}
      {% endfor %}
    </ul>
  </div>
  {% endif %}
{% endfor %}
