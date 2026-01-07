% define CONSTANT
% In MATLAB functions, variables are local, so we define this in main
function main()
    COST_PER_POUND = 7.99;
    
    % create an order object
    order1 = Order();
    
    tempName = input("Enter coffee name (one word please): ", "s");
    order1.setName(tempName);
    
    tempPounds = input("Enter # of pounds: ");
    order1.setPounds(tempPounds);
    
    order1.setCostPerPound(COST_PER_POUND);
    
    finalizeOrder(order1);
end

function finalizeOrder(newOrder)
    cost = 0;
    
    newOrder.displayOrder();
    cost = newOrder.calcCost();
    fprintf("Your order costs $%0.2f\n", cost);
end

% call main
main()