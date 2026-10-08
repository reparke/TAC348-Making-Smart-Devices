---
title: How This Site Is Built
layout: single
toc: true
toc_label: "On This Page"
toc_sticky: true
description: "How TAC 348 course materials are authored in Markdown, organized with Jekyll and Minimal Mistakes, and published through GitHub Pages."
---

This site keeps the course's student-facing pages and their source files in one [public repository](https://github.com/reparke/TAC348-Making-Smart-Devices). Faculty can browse the published materials, inspect the Markdown behind them, and see how the pages are organized and revised. For the course overview and examples of its materials, see [For Educators](/for_educators.html).

## Authoring the Materials

Rob authors course materials directly in [Typora](https://typora.io/) as Markdown. The repository contains the source for the [weekly schedule](https://github.com/reparke/TAC348-Making-Smart-Devices/blob/main/schedule.md), [assignments](https://github.com/reparke/TAC348-Making-Smart-Devices/tree/main/_assignments), [lectures](https://github.com/reparke/TAC348-Making-Smart-Devices/tree/main/_lectures), [readings](https://github.com/reparke/TAC348-Making-Smart-Devices/tree/main/_readings), and [reference guides](https://github.com/reparke/TAC348-Making-Smart-Devices/tree/main/_reference). Images and diagrams sit beside many of the Markdown pages in matching `.assets` folders, so the source and its illustrations can be inspected together.

The repository also keeps [exercise code](https://github.com/reparke/TAC348-Making-Smart-Devices/tree/main/_exercises) and [archived syllabi and weekly plans](https://github.com/reparke/TAC348-Making-Smart-Devices/tree/main/archive). The archive is available in the repository for comparison; the Jekyll configuration excludes it from the published site build.

## From Markdown to Site Pages

[Jekyll](https://jekyllrb.com/) builds the website using the [Minimal Mistakes](https://mmistakes.github.io/minimal-mistakes/) theme. The site's [_config.yml](https://github.com/reparke/TAC348-Making-Smart-Devices/blob/main/_config.yml) defines collections for assignments, lectures, readings, and reference pages, along with shared layout defaults. Index pages such as [Assignments](/assignments.html) and [Reference](/reference.html) draw from those collections.

Site-specific presentation lives in [stylesheets](https://github.com/reparke/TAC348-Making-Smart-Devices/tree/main/_sass), [assets](https://github.com/reparke/TAC348-Making-Smart-Devices/tree/main/assets), and [custom includes](https://github.com/reparke/TAC348-Making-Smart-Devices/tree/main/_includes). These extend the theme without changing the Markdown source of each lesson. The [Gemfile](https://github.com/reparke/TAC348-Making-Smart-Devices/blob/main/Gemfile) lists the Jekyll and GitHub Pages dependencies used for a local build.

## Lecture Source and Slides

Lecture Markdown files include Marp-compatible front matter. For example, the [Electricity lecture](https://github.com/reparke/TAC348-Making-Smart-Devices/blob/main/_lectures/week01/lecture_electricity.md) sets `marp: true` and selects the `tac` theme. The repository includes [custom Marp themes](https://github.com/reparke/TAC348-Making-Smart-Devices/tree/main/marp-custom-themes). These files document the source format and styling; they do not establish a required slide-export routine for other instructors.

## Publishing and Versions

Approved changes are merged into the repository's `main` branch. GitHub Pages then builds and deploys the site. The [_config.yml](https://github.com/reparke/TAC348-Making-Smart-Devices/blob/main/_config.yml) URL and [CNAME](https://github.com/reparke/TAC348-Making-Smart-Devices/blob/main/CNAME) point the published site to [makingsmartdevices.com](https://makingsmartdevices.com/). The repository's [term tags](https://github.com/reparke/TAC348-Making-Smart-Devices/tags) and [Course History](/course_history.html) offer starting points for comparing versions.

For an educator adapting this structure, the useful pattern is a Markdown source for each page, Jekyll collections for recurring material, and a repository that preserves both current files and dated course versions.
