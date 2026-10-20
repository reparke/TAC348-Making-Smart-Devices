(function () {
  function updateScrollableTables() {
    document.querySelectorAll('.table-scroll').forEach(function (container) {
      if (container.scrollWidth > container.clientWidth + 1) {
        container.tabIndex = 0;
        container.setAttribute('role', 'region');
        container.setAttribute('aria-label', 'Scrollable table');
      } else if (!container.classList.contains('table-scroll--wide')) {
        container.removeAttribute('tabindex');
        container.removeAttribute('role');
        container.removeAttribute('aria-label');
      }
    });
  }

  function enhanceTables() {
    document.querySelectorAll('.page__content table').forEach(function (table) {
      if (table.parentElement.classList.contains('table-scroll')) return;
      var container = document.createElement('div');
      container.className = 'table-scroll';
      var columns = Math.max.apply(null, Array.from(table.rows, function (row) {
        return Array.from(row.cells).reduce(function (count, cell) {
          return count + cell.colSpan;
        }, 0);
      }));
      if (columns >= 4) {
        container.classList.add('table-scroll--wide');
        container.tabIndex = 0;
        container.setAttribute('role', 'region');
        container.setAttribute('aria-label', 'Scrollable table');
      }
      table.parentNode.insertBefore(container, table);
      container.appendChild(table);
    });
    updateScrollableTables();
    if ('ResizeObserver' in window) {
      var observer = new ResizeObserver(updateScrollableTables);
      document.querySelectorAll('.table-scroll').forEach(function (container) {
        observer.observe(container);
        var table = container.querySelector('table');
        if (table) observer.observe(table);
      });
    }
    if (document.fonts && document.fonts.ready) {
      document.fonts.ready.then(updateScrollableTables);
    }
  }

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', enhanceTables, { once: true });
  } else {
    enhanceTables();
  }
  window.addEventListener('resize', function () {
    requestAnimationFrame(updateScrollableTables);
  });
}());
