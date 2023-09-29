class Cashier {
    int n, discount;
    int curr_customer=0;
    unordered_map<int, int> prod_to_price;
public:
    Cashier(int ni, int discounti, vector<int>& products, vector<int>& prices) {
        n=ni;
        discount=discounti;
        for (int i=0; i<products.size(); i++) {
            prod_to_price[products[i]] = prices[i];
        }
    }
    
    double getBill(vector<int> product, vector<int> amount) {
        curr_customer++;
        double total=0;
        for (int i=0; i<product.size(); i++) {
            int price = prod_to_price[product[i]];
            total += price * amount[i];
        }
        if (curr_customer == n) {
            curr_customer = 0;
            total *= ((100.0-discount)/100.0);
        }
        return total;
    }
};

/**
 * Your Cashier object will be instantiated and called as such:
 * Cashier* obj = new Cashier(n, discount, products, prices);
 * double param_1 = obj->getBill(product,amount);
 */
