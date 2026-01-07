% Comments: single line
%{
  Comments: Multi-line
%}

% Program structure
%  MATLAB scripts execute commands in order
%  No explicit "main" function is strictly required for simple scripts,
%  but you can define one to match the C++/Java structure.

function main()
% variable declarations
% Variables are dynamically typed (no int/double declaration needed)
    a = 8;
    x = 3.14;
    message = "Hello World!"; % String using double quotes 
    gotMilk = true;

    % Output
    disp("This will print to the console");
    disp(message);
    fprintf("The value of X is %f\n", x); % using fprintf for formatted output
    disp("---------------------------");

    % Input
    % input() parses the input. 
    a = input("Enter a integer: ");
    disp(a);

    % Reading a string
    % The "s" argument tells MATLAB to read as a string/character array
    message = input("Enter a single word: ", "s");
    disp(message);

    % MATLAB input reads the whole line if "s" is used, effectively like getline
    message = input("Enter multiple words: ", "s");
    disp(message);
    disp("---------------------------");

    % If statements
    if gotMilk == true
        disp("You've got milk");
    elseif gotMilk == false
        disp("There is an absence of milk!");
    else
        disp("This will never execute");
    end
    disp("---------------------------");

    % while loops
    a = 7;
    while a ~= 0
        disp("This loop will continue until you enter 0.");
        a = input("Enter a number: ");
    end
    disp("----------------------------");

    % for loops
    a = input("Enter a positive number to sum: ");
    total = 0;
    % MATLAB loops are inclusive of the end range (0 to a)
    for i = 0:a
        total = total + i;
    end

    % output result
    fprintf("The summation of %d is %d\n", a, total);
    disp("---------------------------");

% call main
main()