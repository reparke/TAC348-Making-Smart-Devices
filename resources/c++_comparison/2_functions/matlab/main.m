% define main function
% In MATLAB, if a script contains local functions (like calcSumSquares below), 
% the script itself must be implemented as a function (like main here).

function main()
  a = 0;
  b = 0;
  result = 0;

  disp("Enter two integers: ");
  a = input("");
  b = input("");

  % calling function calcSumSquares with inputs a and b
  result = calcSumSquares(a, b);

  % calling function display result
  displayResult(a, b, result);

end

% calcSumSquares
% Takes two parameters
% Returns the result of the computation
function result = calcSumSquares(num1, num2)
  result = num1 * num1 + num2 * num2;
end


% displayResult
% Takes three parameters to display to command window
% Returns nothing (so no return variable specified in function definition)
function displayResult(num1, num2, result)
  fprintf("The sum of squares of %d and %d is %d\n", num1, num2, result);
end

% call main function
main()