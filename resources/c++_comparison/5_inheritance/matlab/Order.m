% In MATLAB, classes are defined in a 'classdef' block.
% We inherit from 'handle' so that the object behaves like a Reference type 
% (like Java/Python/C++ objects). If we don't, it behaves like a Value type 
% (like a C++ struct passed by value).

classdef Order < handle
   properties (Access = private)
      name
      pounds
      costPerPound
   end
   
   methods
      % default constructor
      function obj = Order()
          obj.name = "";
          obj.pounds = 0;
          obj.costPerPound = 0.0;
      end
      
      % get / set methods
      function n = getName(obj)
          n = obj.name;
      end
      
      function p = getPounds(obj)
          p = obj.pounds;
      end
      
      function c = getCostPerPound(obj)
          c = obj.costPerPound;
      end
      
      function setName(obj, newName)
          obj.name = newName;
      end
      
      function setPounds(obj, newPounds)
          obj.pounds = newPounds;
      end
      
      function setCostPerPound(obj, newCost)
          obj.costPerPound = newCost;
      end
      
      % methods
      %{
        calcCost
        input: none
        output: returns pounds * costPerPound
      %}
      function c = calcCost(obj)
          c = obj.pounds * obj.costPerPound;
      end
      
      %{
        displayOrder
        input: none
        output: none
        side-effect: prints a summary of the order to the screen
      %}
      function displayOrder(obj)
          fprintf("Order: %s for %d lbs @ $%0.2f/lb\n", ...
              obj.name, obj.pounds, obj.costPerPound);
      end
   end
end