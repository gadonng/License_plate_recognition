plateRecognition.controller('uploadCtrl', ['$scope', 'uploadPlate','plate',function($scope, upload, plate){
	$scope.data = upload.info;

	$scope.upload = function (){
		console.log ($scope.data.filename);
	}

	$scope.onUploadSuccess = function (response) {
			$scope.data.id = response.data.id;
	}

}]);
