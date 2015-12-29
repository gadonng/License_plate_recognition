plateRecognition.controller('plateListCtrl', ['$scope','plate',function ($scope, plate){
  $scope.data = plate.info;

  $scope.getPlateList = function (){
    plate.getPlateList();
  };

  $scope.next = function () {
    plate.next();
  };

  $scope.prev = function () {
    plate.prev();
  };

  $scope.editPlate = function (index) {
    plate.editPlate(index);
  };
  
}]);
