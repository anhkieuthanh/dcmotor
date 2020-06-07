var app = angular.module("app", []);
app.controller("dcMotor", ['$scope', function($scope) {
    var status1 = "CCW";
    var status2 = "CW";
    $scope.resetData = function() {
        $scope.data.input = "";
    }
    
}]);