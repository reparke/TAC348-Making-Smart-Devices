(function () {
  "use strict";

  var hero = document.querySelector(".home-refresh .page__hero--overlay");
  var imageSets = window.homeHeroImageSets || {};
  var mobileLayout = window.matchMedia("(max-width: 700px)");
  var images = mobileLayout.matches ? imageSets.mobile : imageSets.desktop;
  images = images || [];

  if (!hero || images.length < 2) {
    return;
  }

  var reduceMotion = window.matchMedia("(prefers-reduced-motion: reduce)");
  var current = Number.parseInt(document.documentElement.dataset.homeHero || "0", 10);
  var interval = 10000;
  var timer = null;
  var userPaused = false;
  var imageSetChange = 0;
  var initialReady = false;

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

  hero.insertBefore(secondLayer, hero.firstChild);
  hero.insertBefore(firstLayer, hero.firstChild);

  function loadImage(url, onReady) {
    var image = new Image();
    image.addEventListener("load", function () {
      if (typeof image.decode === "function") {
        image.decode().then(onReady, function () {});
      } else {
        onReady();
      }
    }, { once: true });
    image.src = url;
  }

  function revealInitialImage(change) {
    var selectedUrl = images[current];
    firstLayer.style.backgroundImage = backgroundFor(selectedUrl);
    loadImage(selectedUrl, function () {
      if (change !== imageSetChange) {
        return;
      }
      delete document.documentElement.dataset.homeHero;
      hero.style.backgroundImage = "none";
      initialReady = true;
      updateToggle();
      scheduleNext();
    });
  }

  revealInitialImage(imageSetChange);

  function updateActiveImage(change) {
    var selectedIndex = current;
    var selectedUrl = images[selectedIndex];
    loadImage(selectedUrl, function () {
      if (change !== imageSetChange) {
        return;
      }
      if (selectedIndex !== current) {
        updateActiveImage(change);
        return;
      }
      var activeLayer = firstLayer.classList.contains("is-active") ? firstLayer : secondLayer;
      activeLayer.style.backgroundImage = backgroundFor(selectedUrl);
    });
  }

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
    toggle.hidden = !initialReady || reduceMotion.matches;
  }

  mobileLayout.addEventListener("change", function () {
    images = mobileLayout.matches ? imageSets.mobile : imageSets.desktop;
    var change = ++imageSetChange;
    if (!initialReady) {
      revealInitialImage(change);
    } else {
      updateActiveImage(change);
    }

    images.forEach(function (url, index) {
      if (index !== current) {
        var image = new Image();
        image.src = url;
      }
    });
  });

  function stopTimer() {
    if (timer !== null) {
      window.clearTimeout(timer);
      timer = null;
    }
  }

  function scheduleNext() {
    stopTimer();
    if (initialReady && !userPaused && !reduceMotion.matches && !document.hidden) {
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
