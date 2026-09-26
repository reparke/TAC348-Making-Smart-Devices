(function () {
  "use strict";

  var hero = document.querySelector(".home-refresh .page__hero--overlay");
  var images = window.homeHeroImages || [];

  if (!hero || images.length < 2) {
    return;
  }

  var reduceMotion = window.matchMedia("(prefers-reduced-motion: reduce)");
  var current = Number.parseInt(document.documentElement.dataset.homeHero || "0", 10);
  var interval = 10000;
  var timer = null;
  var userPaused = false;
  var hovering = false;

  if (!Number.isInteger(current) || current < 0 || current >= images.length) {
    current = 0;
  }

  var firstLayer = document.createElement("div");
  var secondLayer = document.createElement("div");
  firstLayer.className = "home-hero__image is-active";
  secondLayer.className = "home-hero__image";
  firstLayer.setAttribute("aria-hidden", "true");
  secondLayer.setAttribute("aria-hidden", "true");

  function backgroundFor(url) {
    return "linear-gradient(rgba(0,0,0,0.58), rgba(0,0,0,0.58)), url(\"" + url + "\")";
  }

  firstLayer.style.backgroundImage = backgroundFor(images[current]);
  hero.insertBefore(secondLayer, hero.firstChild);
  hero.insertBefore(firstLayer, hero.firstChild);
  delete document.documentElement.dataset.homeHero;
  hero.style.backgroundImage = "none";

  images.forEach(function (url, index) {
    if (index !== current) {
      var image = new Image();
      image.src = url;
    }
  });

  var toggle = document.createElement("button");
  toggle.type = "button";
  toggle.className = "home-hero__toggle";
  hero.appendChild(toggle);

  function updateToggle() {
    var paused = userPaused || reduceMotion.matches;
    toggle.textContent = paused ? "Resume images" : "Pause images";
    toggle.setAttribute("aria-pressed", String(paused));
    toggle.hidden = reduceMotion.matches;
  }

  function stopTimer() {
    if (timer !== null) {
      window.clearTimeout(timer);
      timer = null;
    }
  }

  function scheduleNext() {
    stopTimer();
    if (!userPaused && !hovering && !reduceMotion.matches && !document.hidden) {
      timer = window.setTimeout(showNext, interval);
    }
  }

  function showNext() {
    var next = (current + 1) % images.length;
    var activeLayer = firstLayer.classList.contains("is-active") ? firstLayer : secondLayer;
    var incomingLayer = activeLayer === firstLayer ? secondLayer : firstLayer;

    incomingLayer.style.backgroundImage = backgroundFor(images[next]);
    incomingLayer.classList.add("is-active");
    activeLayer.classList.remove("is-active");
    current = next;
    scheduleNext();
  }

  toggle.addEventListener("click", function () {
    userPaused = !userPaused;
    updateToggle();
    scheduleNext();
  });

  hero.addEventListener("mouseenter", function () {
    hovering = true;
    stopTimer();
  });

  hero.addEventListener("mouseleave", function () {
    hovering = false;
    scheduleNext();
  });

  hero.addEventListener("focusin", function (event) {
    if (event.target !== toggle) {
      userPaused = true;
      updateToggle();
    }
    stopTimer();
  });

  document.addEventListener("visibilitychange", scheduleNext);
  reduceMotion.addEventListener("change", function () {
    updateToggle();
    scheduleNext();
  });

  updateToggle();
  scheduleNext();
}());
