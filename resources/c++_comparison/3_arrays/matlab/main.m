% define main function
function main()
    % create array of numbers
    % Unlike C++, MATLAB arrays are dynamic and can be resized
    numbers = []; 
    sizeOfArray = 4;
    
    % fill array with user input
    for i = 1:sizeOfArray
        % Note: MATLAB Indices start at 1, unlike C++ which starts at 0
        prompt = "Enter num: ";
        numbers(i) = input(prompt);
    end
    
    % print array
    disp("The numbers in the array are:");
    for i = 1:length(numbers)
        disp(numbers(i));
    end
    
    % call method calcSum and store the return value
    sumVal = calcSum(numbers);
    fprintf("The sum of the numbers is %d\n", sumVal);
end
  
%{
   calcSum
   input: array of ints
   output: int
   desc: adds all the values in the array and returns the sum
%}
function sumVal = calcSum(nums)
    sumVal = 0;
    for i = 1:length(nums)
        sumVal = sumVal + nums(i);
    end
end

% call main
main()