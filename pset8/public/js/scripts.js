/* global google */
/* global _ */
/**
 * scripts.js
 *
 * Computer Science 50
 * Problem Set 8
 *
 * Global JavaScript.
 */

// Google Map
var map;

// markers for map
var markers = [];

// info window
var infoWindow = new google.maps.InfoWindow;

// execute when the DOM is fully loaded
$(function() {

    // styles for map
    // https://developers.google.com/maps/documentation/javascript/styling
    var styles = [

        // hide Google's labels
        {
            featureType: "all",
            elementType: "labels",
            stylers: [
                {visibility: "off"}
            ]
        },

        // hide roads
        {
            featureType: "road",
            elementType: "geometry",
            stylers: [
                {visibility: "off"}
            ]
        }

    ];

    // options for map
    // https://developers.google.com/maps/documentation/javascript/reference#MapOptions
    var options = {
        center: {lat: 53.472225, lng: -2.2936244}, // Manchester, ENG ,
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        maxZoom: 14,
        panControl: true,
        styles: styles,
        zoom: 13,
        zoomControl: true
    };

    // get DOM node in which map will be instantiated
    var canvas = $("#map-canvas").get(0);

    // instantiate map
    map = new google.maps.Map(canvas, options);

    // configure UI once Google Map is idle (i.e., loaded)
    google.maps.event.addListenerOnce(map, "idle", configure);

});

/**
 * Adds marker for place to map.
 */
function addMarker(place)
{
    // create a new marker
    var marker;
    
    var latLng = new google.maps.LatLng(parseFloat(place.latitude), parseFloat(place.longitude));
    var markerString = place.place_name + ' (' + place.postal_code + ')';
    
    marker = new MarkerWithLabel({
        position: latLng,
        map: map,
        labelContent: markerString,
        labelAnchor: new google.maps.Point(27, 0),
        labelClass: 'label'
    });
    
    //add marker to markers array
    markers.push(marker);
    
    // set the map on all markers in the array
    function setMapOnAll(map) {
        for (var i = 0; i < markers.length; i++) {
            markers[i].setMap(map);
        }
    }
        // add a click listener to marker and run anonymous function    
        marker.addListener('click', function() {
            
            // set content to ajax loader gif in img directory
            infoWindow.setContent('<div class ="newsList"><img class="loading" src="img/ajax-loader.gif"/></div>');
            
            // retrieve JSON from articles.php and dynamically create a string of HTML from it
            var parameters = {
                geo: place.place_name + ',' + place.admin_name1
            };
            
            $.getJSON("articles.php", parameters)
            .done(function(data, textStatus, jqXHR) {
                var length = data.length;
                var articlesHTML = '<div class="newsList"><ul>';
        
                // iterate through JSON adding each item to an unordered list
                for(var i = 0; i < length; i++){
                    articlesHTML += '<li class="listItem"><a class="newsLink" href="' + data[i].link + '">' + data[i].title + '</a></li>';
                }
            
                articlesHTML += '</ul></div>';
    
                if (length == 0){
                    articlesHTML = '<div class="newsList"><p>Slow News Day!</p></div>';
                }

                // create a new info window and set its content to the HTML string created above
                infoWindow.setContent(articlesHTML);
            });
            
            // open info window
            infoWindow.open(map, marker);
  });
}

/**
 * Configures application.
 */
function configure()
{
    // update UI after map has been dragged
    google.maps.event.addListener(map, "dragend", function() {
        update();
    });

    // update UI after zoom level changes
    google.maps.event.addListener(map, "zoom_changed", function() {
        update();
    });

    // remove markers whilst dragging
    google.maps.event.addListener(map, "dragstart", function() {
        removeMarkers();
    });

    // configure typeahead
    // https://github.com/twitter/typeahead.js/blob/master/doc/jquery_typeahead.md
    $("#q").typeahead({
        autoselect: true,
        highlight: true,
        minLength: 1
    },
    {
        source: search,
        templates: {
            empty: "no places found yet",
            suggestion: _.template('<p><%- place_name %>, <%- admin_name2 %> <span id="postal_code">(<%- postal_code %>)</span></p>')
        }
    });

    // re-center map after place is selected from drop-down
    $("#q").on("typeahead:selected", function(eventObject, suggestion, name) {

        // ensure coordinates are numbers
        var latitude = (_.isNumber(suggestion.latitude)) ? suggestion.latitude : parseFloat(suggestion.latitude);
        var longitude = (_.isNumber(suggestion.longitude)) ? suggestion.longitude : parseFloat(suggestion.longitude);

        // set map's center
        map.setCenter({lat: latitude, lng: longitude});

        // update UI
        update();
    });

    // hide info window when text box has focus
    $("#q").focus(function(eventData) {
        hideInfo();
    });

    // re-enable ctrl- and right-clicking (and thus Inspect Element) on Google Map
    // https://chrome.google.com/webstore/detail/allow-right-click/hompjdfbfmmmgflfjdlnkohcplmboaeo?hl=en
    document.addEventListener("contextmenu", function(event) {
        event.returnValue = true; 
        event.stopPropagation && event.stopPropagation(); 
        event.cancelBubble && event.cancelBubble();
    }, true);

    // update UI
    update();

    // give focus to text box
    $("#q").focus();
}

/**
 * Hides info window.
 */
function hideInfo()
{
    infoWindow.close();
}

/**
 * Removes markers from map.
 */
function removeMarkers()
{
    var length = markers.length;
    
    for (var i = 0; i < length; i++)
    {
        markers[i].setMap(null);
    }
    markers = [];
}

/**
 * Searches database for typeahead's suggestions.
 */
function search(query, cb)
{
    // get places matching query (asynchronously)
    var parameters = {
        geo: query
    };
    $.getJSON("search.php", parameters)
    .done(function(data, textStatus, jqXHR) {

        // call typeahead's callback with search results (i.e., places)
        cb(data);
    })
    .fail(function(jqXHR, textStatus, errorThrown) {

        // log error to browser's console
        console.log(errorThrown.toString());
    });
}

/**
 * Updates UI's markers.
 */
function update() 
{
    // get map's bounds
    var bounds = map.getBounds();
    var ne = bounds.getNorthEast();
    var sw = bounds.getSouthWest();

    // get places within bounds (asynchronously)
    var parameters = {
        ne: ne.lat() + "," + ne.lng(),
        q: $("#q").val(),
        sw: sw.lat() + "," + sw.lng()
    };
    $.getJSON("update.php", parameters)
    .done(function(data, textStatus, jqXHR) {

        // remove old markers from map
        removeMarkers();

        // add new markers to map
        for (var i = 0; i < data.length; i++)
        {
            addMarker(data[i]);
        }
     })
     .fail(function(jqXHR, textStatus, errorThrown) {

         // log error to browser's console
         console.log(errorThrown.toString());
     });
}