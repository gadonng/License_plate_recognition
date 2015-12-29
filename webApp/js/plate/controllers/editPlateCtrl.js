plateRecognition.controller('editPlateCtrl', ['$scope', 'plate', 'main', function($scope, plate, main){
  $scope.data = plate.info;

  $scope.back = function (){
    main.back();
  };

}]);
