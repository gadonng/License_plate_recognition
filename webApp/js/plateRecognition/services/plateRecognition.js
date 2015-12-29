plateRecognition.factory('main', function(){
	var mainObj = {};

	mainObj.info = {};
	mainObj.info.tab = 1;

	// TODO : Use ng-views and routing
	// TODO : ADD Last Tab

	mainObj.back = function (){
		mainObj.info.tab = 3;
	};
	
	return mainObj;
});
