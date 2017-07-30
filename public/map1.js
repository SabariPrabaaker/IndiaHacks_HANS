var firebase = new Firebase("https://hapticaid.firebaseio.com/");

var lat = 12.994077;
var lng = 77.59008100000005;

// sets your location as default
/*
if (navigator.geolocation) {
  navigator.geolocation.getCurrentPosition(function(position) {
    var locationMarker = null;
    if (locationMarker){
      // return if there is a locationMarker bug
      return;
    }

    lat = position.coords["latitude"];
    lng = position.coords["longitude"];

   console.log(lat, lng);

  },
  function(error) {
    console.log("Error: ", error);
  },
  {
    enableHighAccuracy: true
  }
  );
}
*/

//end of navigator


function initMap() {
// Instantiate a directions service.
  var directionsService = new google.maps.DirectionsService;
   var markerArray = [];
  var map = new google.maps.Map(document.getElementById('map'), {
    center: {lat: lat, lng: lng},
    zoom: 18
  });
                 //ADD THE BLOCKAGE HERE 
myLatLng = new google.maps.LatLng(lat, lng);
      // Add marker on user click
  map.addListener('click', function(e) {
    firebase.push({obstacle:{lat: e.latLng.lat(), lng: e.latLng.lng()}});
  });

  // Create a heatmap.
  var heatmap = new google.maps.visualization.HeatmapLayer({
    data: [],
    map: map,
    radius: 18
  });

  firebase.on("child_added", function(snapshot, prevChildKey) {
	  
    // Get latitude and longitude from Firebase.
    var newPosition = snapshot.val().obstacle;

    // Create a google.maps.LatLng object for the position of the marker.
    // A LatLng object literal (as above) could be used, but the heatmap
    // in the next step requires a google.maps.LatLng object.
    var latLng = new google.maps.LatLng(newPosition.lat, newPosition.lng);
    if(google.maps.geometry.spherical
   .computeDistanceBetween(myLatLng,latLng)<10){
        
        
        
       
        
   var url="http://localhost:8081/api?direction=o";    
    console.log("predefined obstacle")
	 $.get(url)     ;
   
    };
    heatmap.getData().push(latLng);

  });                        
            
  
  // Create a renderer for directions and bind it to the map.
  var directionsDisplay = new google.maps.DirectionsRenderer({map: map});

  // Instantiate an info window to hold step text.
  var stepDisplay = new google.maps.InfoWindow;

  // Display the route between the initial start and end selections.
  calculateAndDisplayRoute(
      directionsDisplay, directionsService, markerArray, stepDisplay, map);
  
  
  
}

function calculateAndDisplayRoute(directionsDisplay, directionsService,
    markerArray, stepDisplay, map) {
  // First, remove any existing markers from the map.
  for (var i = 0; i < markerArray.length; i++) {
    markerArray[i].setMap(null);
  }

  // Retrieve the start and end locations and create a DirectionsRequest using
  // WALKING directions.
  /*directionsService.route({
    origin: "12.934916129182422,77.69438982009888",  
    destination:"12.934137111902253,77.69541442394257",
    travelMode: google.maps.TravelMode.WALKING
  }, function(response, status) {
    // Route the directions and pass the response to a function to create
    // markers for each step.
    if (status === google.maps.DirectionsStatus.OK) {
     // document.getElementById('warnings-panel').innerHTML =
       //   '<b>' + response.routes[0].warnings + '</b>';
      directionsDisplay.setDirections(response);
      showSteps(response, markerArray, stepDisplay, map);
    } else {
      window.alert('Directions request failed due to ' + status);
    }
  }); */
}

function showSteps(directionResult, markerArray, stepDisplay, map) {
  // For each step, place a marker, and add the text to the marker's infowindow.
  // Also attach the marker to an array so we can keep track of it and remove it
  // when calculating new routes.
  var myRoute = directionResult.routes[0].legs[0];
  for (var i = 1; i < myRoute.steps.length; i++) {
    
    var marker = markerArray[i] = markerArray[i] || new google.maps.Marker;
    marker.setMap(map);
    marker.setPosition(myRoute.steps[i].start_location);
    attachInstructionText(
        stepDisplay, marker, myRoute.steps[i].instructions,myRoute.steps[i].distance,myRoute.steps[i].duration, map);
        
        
        //run timer for duration 
        //hit get request with direction
  }









            






}



function attachInstructionText(stepDisplay, marker, text,distance,duration, map) {
  google.maps.event.addListener(marker, 'click', function() {
    // Open an info window when the marker is clicked on, containing the text
    // of the step.
    
    stepDisplay.setContent(text);
    stepDisplay.open(map, marker);
    
  });
}

