(function ($, Drupal, undefined) {
  Drupal.behaviors.als_link_to_modal = {
    attach: function (context, settings) {

      $(settings.als_link_to_modal).each(function(k,row) {
        var el = $('a[href="/'+row[0]+'"]');
        if (row[2].length > 0) el = el.filter(row[2]);
        if (el.length > 0) {
          el.each(function() {
            $(this).attr('href', row[1]).addClass(row[3]);
          });
        }
      });

    }
  };
})(jQuery, Drupal);