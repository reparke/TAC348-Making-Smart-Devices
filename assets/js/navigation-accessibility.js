(function () {
  "use strict";

  if (window.msdNavigationAccessibilityInstalled) {
    return;
  }
  window.msdNavigationAccessibilityInstalled = true;

  function init() {
    var nav = document.querySelector(".greedy-nav");
    if (!nav) {
      return;
    }

    var brand = nav.querySelector(".site-title");
    var visible = nav.querySelector(".visible-links");
    var hidden = nav.querySelector(".hidden-links");
    var menu = nav.querySelector(".greedy-nav__toggle");
    var search = nav.querySelector(".search__toggle");
    var links = Array.prototype.slice.call(visible.children).concat(Array.prototype.slice.call(hidden.children));
    var scheduled = false;
    var observer;

    function currentPath(url) {
      return new URL(url, window.location.href).pathname.replace(/\.html$/, "").replace(/\/$/, "") || "/";
    }

    var path = currentPath(window.location.href);
    Array.prototype.forEach.call(nav.querySelectorAll(".visible-links a, .hidden-links a"), function (link) {
      if (new URL(link.href).origin === window.location.origin && currentPath(link.href) === path) {
        link.setAttribute("aria-current", "page");
      }
    });

    function labelPermalinks() {
      Array.prototype.forEach.call(document.querySelectorAll("a.header-link"), function (link) {
        var heading = link.closest("h1, h2, h3, h4, h5, h6");
        if (heading) {
          var text = heading.cloneNode(true);
          Array.prototype.forEach.call(text.querySelectorAll("a.header-link"), function (anchor) { anchor.remove(); });
          link.setAttribute("aria-label", "Permalink to " + text.textContent.trim());
        }
      });
    }

    labelPermalinks();
    window.addEventListener("load", labelPermalinks, { once: true });
    new MutationObserver(labelPermalinks).observe(document.body, { childList: true, subtree: true });

    function closeMenu() {
      hidden.classList.add("hidden");
      menu.setAttribute("aria-expanded", "false");
    }

    function syncMenu() {
      menu.setAttribute("aria-expanded", String(!menu.classList.contains("hidden") && !hidden.classList.contains("hidden")));
    }

    function linksFit() {
      if (!visible.children.length) {
        return true;
      }
      var first = visible.querySelector("a");
      var last = visible.lastElementChild.querySelector("a");
      return first.getBoundingClientRect().left >= brand.getBoundingClientRect().right + 8 &&
        last.getBoundingClientRect().right <= search.getBoundingClientRect().left - 8;
    }

    function repairOverflow() {
      scheduled = false;
      observer.disconnect();
      closeMenu();
      // Measure the complete navigation without reserving room for the menu.
      // The theme's cached breakpoints do not account for the brand width.
      menu.classList.add("hidden");
      links.forEach(function (link) { visible.appendChild(link); });

      if (!linksFit()) {
        menu.classList.remove("hidden");
        while (visible.children.length && !linksFit()) {
          hidden.insertBefore(visible.lastElementChild, hidden.firstElementChild);
        }
      }

      menu.classList.toggle("hidden", hidden.children.length === 0);
      menu.setAttribute("count", String(hidden.children.length));
      syncMenu();
      observer.observe(visible, { childList: true });
      observer.observe(hidden, { childList: true });
    }

    function scheduleRepair() {
      if (!scheduled) {
        scheduled = true;
        window.setTimeout(repairOverflow, 50);
      }
    }

    menu.setAttribute("aria-controls", "primary-overflow-links");
    hidden.id = "primary-overflow-links";
    menu.addEventListener("click", function () {
      window.setTimeout(syncMenu, 0);
    });
    hidden.addEventListener("mouseleave", function () {
      window.setTimeout(syncMenu, 1100);
    });
    document.addEventListener("keydown", function (event) {
      if (event.key === "Escape" && !hidden.classList.contains("hidden")) {
        closeMenu();
        menu.focus();
      }
    });
    window.addEventListener("resize", scheduleRepair);
    window.addEventListener("load", scheduleRepair, { once: true });
    observer = new MutationObserver(scheduleRepair);
    observer.observe(visible, { childList: true });
    observer.observe(hidden, { childList: true });
    scheduleRepair();
  }

  if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", function () { window.setTimeout(init, 0); });
  } else {
    window.setTimeout(init, 0);
  }
}());
