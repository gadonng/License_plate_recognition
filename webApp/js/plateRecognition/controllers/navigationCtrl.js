plateRecognition.controller('navigationCtrl', ['$scope', 'main', 'plate', function($scope, main, plate){
	$scope.data = main.info;
	$scope.plateData = plate.info;

	$scope.search = function (){
		plate.getPlateList();
	};
}]);
