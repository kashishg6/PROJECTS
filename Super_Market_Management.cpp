#include <iostream>
#include <string>
#include <stack>

using namespace std;

struct Product {
    string id;
    string name;
    int originalPrice;
    int price;
    int quantity;
    Product* next;
};

typedef Product* ProductNode;

struct User {
    string name;
    string surname;
    string contact;
    string address;
    string date;
};

typedef User* UserNode;

struct Admin {
    string username;
    string password;
    
};

typedef Admin* AdminNode;

struct BucketItem {
    string productId;
    string productName;
    int productPrice;
    int ogproductPrice;
    int productQuantity;
    BucketItem* next;
};

typedef BucketItem* BucketItemNode;

struct InvoiceRecord {
    string date;
    int amount;
    int ogtotal; 
    InvoiceRecord* next;
};

typedef InvoiceRecord* InvoiceRecordNode;

struct node1
{
    int pid;
    string product_name;
    int product_price;
    int product_quantity;
    struct node1 *next;
};

struct commodity
{
    int pid;
    int product_quantity;
    struct commodity *next;
};

struct node
{
    int itemid;
    string itemname;
    int price;
    int quantity;
    struct node *next;
};

int login(AdminNode& adminHead) {
    string username;
    string password;

    AdminNode adminHead2;
    AdminNode adminHead3;
    AdminNode adminHead4;

    adminHead = new Admin;
    adminHead2 = new Admin;
    adminHead3 = new Admin;
    adminHead4 = new Admin;

    adminHead->username = "sm9779";
    adminHead->password = "SRM@55";
    
    adminHead2->username = "sg2213";
    adminHead2->password = "SRM@25";

    adminHead3->username = "kg1952";
    adminHead3->password = "SRM@24";

    adminHead4->username = "ADMIN";
    adminHead4->password = "ADMIN@123";

    cout << "Enter the Username: " << endl;
    cin >> username;
    cout << "Enter the Password: " << endl;
    cin >> password;
    if (username == adminHead->username && password == adminHead->password) {
        return 1;
    }
    else if (username == adminHead2->username && password == adminHead2->password) {
        return 2;
    }
    else if (username == adminHead3->username && password == adminHead3->password) {
        return 3;
    }
    else if (username == adminHead4->username && password == adminHead4->password) {
        return 0;
    }
}

InvoiceRecordNode createInvoiceRecord(InvoiceRecordNode top, int sum, int ogtotal, string date) {
    InvoiceRecordNode record = new InvoiceRecord;
    record->date = date;
    record->amount = sum;
    record->ogtotal = ogtotal; 
    record->next = top;
    top = record;
    return top;
}

void calculateTotalRevenue(InvoiceRecordNode top) {
    int totalRevenue = 0;
    int totalogRevenue = 0;
    string endDate;
    cout << "Enter the date on which you want to calculate revenue (DD-MM-YYYY): " << endl;
    cin >> endDate;

    while (top != nullptr) {
        if (top->date == endDate) {
            totalRevenue += top->amount;
            totalogRevenue += top->ogtotal; 
        }
        top = top->next;
    }

    if (totalRevenue > 0) {
        int profit = totalRevenue - totalogRevenue;
        cout << "Total revenue for this duration is: " << totalRevenue << endl;
        cout << "Total profit for this duration is: " << profit << endl;
    } else {
        cout << "There was a problem or there is no record. Please try again :)" << endl;
    }
}

int calculateTotalPrice(BucketItemNode head) {
    int total = 0;
    BucketItemNode temp = head;
    while (temp != nullptr) {
        total += (temp->productQuantity) * (temp->productPrice);
        temp = temp->next;
    }
    return total;
}

ProductNode insertProduct(ProductNode head, string id, string name, int price, int quantity, int originalPrice) {
    ProductNode newNode = new Product;
    newNode->id = id;
    newNode->name = name;
    newNode->price = price;
    newNode->quantity = quantity;
    newNode->originalPrice = originalPrice;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    }
    else {
        ProductNode temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    return head;
}

ProductNode deleteProduct(ProductNode head) {
    string id;
    cout << "Enter the product id of the product to be deleted: ";
    cin >> id;

    if (head == nullptr) {
        cout << "Can't perform deletion since there are no products." << endl;
    }
    else if (head->id == id) {
        ProductNode temp = head;
        head = head->next;
        delete temp;
    }
    else {
        ProductNode temp = head;
        ProductNode prev = nullptr;
        while (temp != nullptr && temp->id != id) {
            prev = temp;
            temp = temp->next;
        }
        if (temp != nullptr) {
            prev->next = temp->next;
            delete temp;
        }
        else {
            cout << "Product not found." << endl;
        }
    }

    return head;
}

ProductNode userInsertProduct(ProductNode head) {
    int price, quantity, originalPrice;
    string id, name;
    cout << "Enter item ID: ";
    cin >> id;
    cout << "Enter product name: ";
    cin >> name;
    cout << "Enter the original price of the product at which you have purchased it: ";
    cin >> originalPrice;
    cout << "Enter price: ";
    cin >> price;
    cout << "Enter quantity: ";
    cin >> quantity;
    head = insertProduct(head, id, name, price, quantity, originalPrice);
    cout << "New product is added :)" << endl;
    return head;
}

string checkProductName(ProductNode head) {
    string productName;
    while (1) {
        cout << "Enter Product Name: ";
        cin >> productName;
        ProductNode temp = head;
        while (temp != nullptr) {
            if (temp->name == productName) {
                return temp->id;
            }
            temp = temp->next;
        }
        cout << "Product not found. Please try again." << endl;
    }
}

ProductNode updateProductQuantityById(ProductNode head, int newQuantity, string productId) {
    ProductNode temp = head;
    while (temp != nullptr) {
        if (temp->id == productId) {
            if (temp->quantity >= newQuantity) {
                temp->quantity -= newQuantity;
                return head;
            }
            else {
                if (temp->quantity < newQuantity) {
                    char ch;
                    cout << "We don't have enough stock; we have only " << temp->quantity << " quantity. Do you want this?" << endl;
                    cout << "If Yes, then press Y" << endl;
                    cin >> ch;
                    if (ch == 'Y') {
                        temp->quantity = 0;
                        return head;
                    }
                    return head;
                }
                else if (temp->quantity == 0) {
                    cout << "Not enough quantity available." << endl;
                    return head;
                }
            }
        }
        temp = temp->next;
    }

    cout << "Product not found." << endl;
    return head;
}

ProductNode updateProductQuantityByName(ProductNode head, int newQuantity, string productName) {
    ProductNode temp = head;
    while (temp != nullptr) {
        if (temp->name == productName) {
            if (temp->quantity >= newQuantity) {
                temp->quantity -= newQuantity;
                return head;
            }
            else {
                if (temp->quantity < newQuantity) {
                    char ch;
                    cout << "We don't have enough stock; we have only " << temp->quantity << " quantity. Do you want this?" << endl;
                    cout << "If Yes, then press Y" << endl;
                    cin >> ch;
                    if (ch == 'Y') {
                        temp->quantity = 0;
                        return head;
                    }
                    return head;
                }
                else if (temp->quantity == 0) {
                    cout << "Not enough quantity available." << endl;
                    return head;
                }
            }
        }
        temp = temp->next;
    }

    cout << "Product not found." << endl;
    return head;
}

ProductNode changeProductQuantity(ProductNode head) {
    string productId;
    int newQuantity;
    cout << "Enter the Product ID for quantity update: ";
    cin >> productId;
    cout << "Enter the new quantity: ";
    cin >> newQuantity;

    ProductNode temp = head;
    while (temp != nullptr) {
        if (temp->id == productId) {
            temp->quantity = newQuantity;
            return head;
        }
        temp = temp->next;
    }

    cout << "Product not found." << endl;
    return head;
}

ProductNode changeProductPrice(ProductNode head) {
    string productId;
    int newPrice;
    cout << "Enter the Product ID for price update: ";
    cin >> productId;
    cout << "Enter the new price: ";
    cin >> newPrice;

    ProductNode temp = head;
    while (temp != nullptr) {
        if (temp->id == productId) {
            temp->price = newPrice;
            return head;
        }
        temp = temp->next;
    }

    cout << "Product not found." << endl;
    return head;
}

string checkProductId(ProductNode head) {
    string productId;
    while (1) {
        cout << "Enter the Product ID of the item you'd like: ";
        cin >> productId;
        ProductNode temp = head;
        while (temp != nullptr) {
            if (temp->id == productId) {
                return productId;
            }
            temp = temp->next;
        }
        cout << "Product not found. Please try again." << endl;
    }
}

BucketItemNode insertBucketItemById(ProductNode head, BucketItemNode head21, string productId, int newQuantity) {
    BucketItemNode newItem = new BucketItem;
    ProductNode temp = head;
    while (temp->id != productId) {
        temp = temp->next;
    }
    newItem->productId = temp->id;
    newItem->productName = temp->name;
    newItem->productPrice = temp->price;
    newItem->productQuantity = newQuantity;
    newItem->ogproductPrice = temp->originalPrice;
    newItem->next = nullptr;
    
    if (head21 == nullptr) {
        head21 = newItem;
    } else {
        BucketItemNode temp1 = head21;
        while (temp1->next != nullptr) {
            temp1 = temp1->next;
        }
        temp1->next = newItem;
    }
    return head21;
}

BucketItemNode insertBucketItemByName(ProductNode head, string productName, int newQuantity) {
    BucketItemNode head2 = nullptr;
    BucketItemNode newItem = new BucketItem;
    ProductNode temp = head;
    while (temp->name != productName) {
        temp = temp->next;
    }
    newItem->productId = temp->id;
    newItem->productName = temp->name;
    newItem->productPrice = temp->price;
    newItem->productQuantity = newQuantity;
    newItem->ogproductPrice = temp->originalPrice;
    newItem->next = nullptr;
    
    if (head2 == nullptr) {
        head2 = newItem;
    } else {
        BucketItemNode tempBucket = head2;
        while (tempBucket->next != nullptr) {
            tempBucket = tempBucket->next;
        }
        tempBucket->next = newItem;
    }
    return head2;
}

BucketItemNode Emptybucket (BucketItemNode head) {
    BucketItemNode temp = head;
    BucketItemNode temp1 = head->next;
    while (temp1 != nullptr)
    {
        delete temp;
        temp=temp1;
        temp1=temp1->next;
    }
    delete temp ;
    head = nullptr;
    return head;
}

UserNode insertUserInfo(UserNode head1) {
    head1 = new User;
    cout << "Enter the Name of the customer: ";
    cin >> head1->name;
    cout << "Enter the Surname of the customer: ";
    cin >> head1->surname;
    cout << "Enter the contact of the customer: ";
    cin >> head1->contact;
    cout << "Enter the address of the customer: ";
    cin >> head1->address;
    cout << "Enter the date of invoice: ";
    cin >> head1->date;
    return head1;
}

string displayUserInfo(UserNode head1) {
    cout << endl << "---------------------------------------------------INVOICE-------------------------------------------------------------" << endl;
    cout << endl << "                                             SHRESHTH CLOTH STORE                                                      " << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Name of Customer: " << head1->name << " " << head1->surname << "                 " << "Contact Number: " << head1->contact << endl;
    cout << "Address: " << head1->address << "                                " << "Date of Invoice : " << head1->date << endl << endl << endl;
    return (head1->date);
}

void displayProducts(ProductNode head) {
    cout << "Product ID \t" << "Product Name \t" << "Product Price \t" << "Product Quantity" << endl;

    while (head != nullptr) {
        cout << head->id << "      \t" << head->name << "      \t" << head->price << "      \t" << head->quantity << endl;
        head = head->next;
    }
}

void displayBucketItems(BucketItemNode head) {
    cout << "Product ID \t" << "Product Name \t" << "Product MRP \t" << "Product Quantity \t  " << "Price" << endl;
    cout << "=============================================================================================================" << endl;
    while (head != nullptr) {
        cout << head->productId << "      \t" << head->productName << "      \t" << head->productPrice << "      \t" << head->productQuantity << "                         " << (head->productQuantity) * (head->productPrice) << endl;
        head = head->next;
    }
}

void totalsumdisplay(int total){
    cout << "-----------------------------------------------------------------------------------------------------------------------";
    cout << endl << "                                                            Total Price = " << total;
    cout << endl << "-----------------------------------------------------------------------------------------------------------------------";
}

int sumofogprice (BucketItemNode head){
    int Total_og = 0;
    while (head != nullptr){
        Total_og +=(head->productQuantity)*(head->ogproductPrice);
        head = head->next;
    }
    return Total_og;
}

void bill_creation(struct node1 *head, int pid, const string &customerName, const string &customerMobile, int product_quantityToReduce);


struct node1 *insertion_at_end(struct node1 *head, int pid, string product_name, int product_price, int product_quantity)
{
    struct node1 *ptr = new node1;
    ptr->pid = pid;
    ptr->product_name = product_name;
    ptr->product_price = product_price;
    ptr->product_quantity = product_quantity;
    ptr->next = nullptr;

    if (head == nullptr)
    {
        head = ptr;
    }
    else
    {
        struct node1 *p = head;
        while (p->next != nullptr)
        {
            p = p->next;
        }
        p->next = ptr;
    }

    return head; // Return the updated head
}

void traversingstore(struct node1 *head)
{
    cout << "PID"
         << "  "
         << "product_name"
         << "  "
         << "product_quantity"
         << "  "
         << "product_price" << endl;
    while (head != nullptr)
    {
        cout << head->pid << "  " << head->product_name << "  " << head->product_price << "  " << head->product_quantity << endl;
        head = head->next;
    }
}

struct node1 *reduceProductproduct_quantity(struct node1 *head, int pid, int product_quantityToReduce)
{
    struct node1 *ptr = head;
    while (ptr != nullptr)
    {
        if (ptr->pid == pid)
        {
            cout << "Current product_quantity for " << ptr->product_name << " (ID: " << ptr->pid << ") is " << ptr->product_quantity << endl;
            if (ptr->product_quantity >= product_quantityToReduce)
            {
                ptr->product_quantity -= product_quantityToReduce;
                cout << "Reduced " << product_quantityToReduce << " of " << ptr->product_name << " (ID: " << ptr->pid << ")" << endl;
                return head; // product found and product_quantity reduced, exit the function
            }
            else
            {
                cout << "Not enough product_quantity in stock for " << ptr->product_name << " (ID: " << ptr->pid << ")" << endl;
                return head; // Not enough product_quantity in stock, exit the function
            }
        }
        ptr = ptr->next;
    }
    cout << "product with ID " << pid << " not found." << endl;
    return head;
}


void updateProductproduct_quantity(struct node1 *head, int pid, int newproduct_quantity)
{
    struct node1 *ptr = head;
    while (ptr != nullptr)
    {
        if (ptr->pid == pid)
        {
            cout << "Updated product_quantity for " << ptr->product_name << " (ID: " << ptr->pid << ") to " << newproduct_quantity << endl;
            ptr->product_quantity = newproduct_quantity;
            return; // product found and product_quantity updated, exit the function
        }
        ptr = ptr->next;
    }
    cout << " product with ID " << pid << " not found." << endl;
}


struct node1 *insertionuser(struct node1 *head)
{
    int pid, product_price, product_quantity;
    string product_name;
    cout << "Enter item ID: ";
    cin >> pid;
    cout << "Enter product name: ";
    cin >> product_name;
    cout << "Enter product_price: ";
    cin >> product_price;
    cout << "Enter product_quantity: ";
    cin >> product_quantity;

    head = insertion_at_end(head, pid, product_name, product_price, product_quantity);
    cout << "New product is added" << endl;

    return head;
}


struct node1 *deletenode1(struct node1 *head)
{
    int pid;
    cout << "Enter the commodity ID to delete: ";
    cin >> pid;

    struct node1 *temp = head;
    struct node1 *temp1 = nullptr;

    // Search for the node1 to delete
    while (temp != nullptr)
    {
        if (temp->pid == pid)
        {
            if (temp1 != nullptr)
            {
                // node1 to delete is not the head
                temp1->next = temp->next;
            }
            else
            {
                // node1 to delete is the head
                head = temp->next;
            }

            // Delete the node1
            delete temp;
            cout << "Item with ID " << pid << " has been deleted." << endl;
            return head;
        }

        temp1 = temp;
        temp = temp->next;
    }

    cout << " product with ID " << pid << " not found." << endl;
    return head;
}
 
struct node1 *updatePIDs(struct node1 *head)
{
    struct node1 *temp = head;
    int newPID = 1;

    while (temp != nullptr)
    {
        temp->pid = newPID;
        newPID++;
        temp = temp->next;
    }

    return head;
}

void bill_creation(struct node1 *head, int pid, const string &customerName, const string &customerMobile, int product_quantityToReduce, stack<commodity *> &billStack)
{
    traversingstore(head);
    struct node1 *ptr = head;

    while (ptr != nullptr)
    {
        if (ptr->pid == pid)
        {
            if (ptr->product_quantity >= product_quantityToReduce)
            {

                ptr->product_quantity -= product_quantityToReduce;

                commodity *productEntry = new commodity;
                productEntry->pid = pid;
                productEntry->product_quantity = product_quantityToReduce;
                productEntry->next = nullptr;

                billStack.push(productEntry);

                return;
            }
            else
            {
                cout << "Not enough product_quantity in stock for " << ptr->product_name << " (ID: " << ptr->pid << ")" << endl;
                return;
            }
        }
        ptr = ptr->next;
    }

    cout << "commodity with ID " << pid << " not found." << endl;
}

void printBill(stack<commodity *> &billStack, struct node1 *head, const string &customerName, const string &customerMobile)
{
    cout<<"=========================================================================================="<<endl;
    cout<<"GSTIN->09AEEPG9990B1ZC                     SALEINVOICE/TAX INVOICE         mob-9412282862                "<<endl;
    cout<<"                                                                                          "<<endl;
    cout<<"==================================RB STORE======================================== "<<endl;
    cout<<"                                                                                       "<<endl;
    cout << "Customer Name: " << customerName << endl;
    cout << "Customer Mobile: " << customerMobile << endl;

    int totalBillAmount = 0;
    while (!billStack.empty())
    {
        commodity *productEntry = billStack.top();
        cout<<"------------------------------------------------------------------------------------------------";
        cout << "commodity ID: " << productEntry->pid << endl;
        cout << "product_quantity Purchased: " << productEntry->product_quantity << endl;

        struct node1 *ptr = head;
        while (ptr != nullptr)
        {
            if (ptr->pid == productEntry->pid)
            {
                int productproduct_price = ptr->product_price;
                int billAmount = productproduct_price * productEntry->product_quantity;
                totalBillAmount += billAmount;
                cout<<"____________________________________________________________________________________________";
                cout << "product_price per unit: " << productproduct_price << endl;
                cout << "Total Bill Amount for this product: " << billAmount << endl;
                break;
            }
            ptr = ptr->next;
        }

        billStack.pop();
    }

    cout << "Total Bill Amount: " << totalBillAmount << endl;
}

struct node *insertionatend(struct node *head, int itemid, string name, int price, int quantity)
{
    struct node *ptr = new node;
    ptr->itemid = itemid;
    ptr->itemname = name;
    ptr->price = price;
    ptr->quantity = quantity;
    ptr->next = nullptr;

    if (head == nullptr)
    {
        head = ptr;
    }
    else
    {
        struct node *p = head;
        while (p->next != nullptr)
        {
            p = p->next;
        }
        p->next = ptr;
    }

    return head; // Return the updated head
}

void linkedListTraversal(struct node *head)
{
    cout << "itemid"
         << "  "
         << "PRODUCTNAME"
         << "  "
         << "PRICE"
         << "  "
         << "QUANTITY" << endl;
    while (head != nullptr)
    {
        cout << head->itemid << "  " << head->itemname << "  " << head->price << "  " << head->quantity << endl;
        head = head->next;
    }
}

struct node *reduceProductQuantity(struct node *head, int itemid, int quantityToReduce)
{
    struct node *ptr = head;
    while (ptr != nullptr)
    {
        if (ptr->itemid == itemid)
        {
            if (ptr->quantity >= quantityToReduce)
            {
                ptr->quantity -= quantityToReduce;
                cout << "Reduced " << quantityToReduce << " of " << ptr->itemname << " (ID: " << ptr->itemid << ")" << endl;

                return head; // Return the updated head
            }
            else
            {
                cout << "Not enough quantity in stock for " << ptr->itemname << " (ID: " << ptr->itemid << ")" << endl;
                return head; // Not enough quantity in stock, exit the function
            }
        }
        ptr = ptr->next;
    }
    cout << "Product with ID " << itemid << " not found." << endl;
    return head; // Return the original head
}

struct node *insertion_user(struct node *head, int itemid, string name, int price, int quantity)
{

    head = insertionatend(head, itemid, name, price, quantity);
    cout << "new product is added" << endl;
    return head;
}

void UpdateProductQuantity(struct node *head, int itemid, int quantityToUpdate)
{
    struct node *ptr = head;
    while (ptr != nullptr)
    {
        if (ptr->itemid == itemid)
        {
            ptr->quantity += quantityToUpdate;
            cout << "Updated " << quantityToUpdate << " of " << ptr->itemname << " (ID: " << ptr->itemid << ")" << endl;
            return; // Product found and quantity updated, exit the function
        }
        ptr = ptr->next;
    }
    cout << "Product with ID " << itemid << " not found." << endl;
}

void billCreation(struct node *head, int &totalBill)
{
    char buyMore = 'y'; 

    cout << "==== Billing ====" << endl;

    do
    {
        int numItemsToBuy;

        cout << "Enter the number of items you want to buy (0 to return to the menu): ";
        cin >> numItemsToBuy;

        if (numItemsToBuy == 0)
        {
            // If the customer doesn't want to buy anything, break the loop and return to the menu.
            break;
        }

        for (int i = 0; i < numItemsToBuy; i++)
        {
            int itemid, quantity;

            cout << "Enter the item ID for item " << (i + 1) << ": ";
            cin >> itemid;
            cout << "Enter the quantity for item " << (i + 1) << ": ";
            cin >> quantity;

            struct node *ptr = head;
            while (ptr != nullptr)
            {
                if (ptr->itemid == itemid)
                {
                    if (ptr->quantity >= quantity)
                    {
                        int itemTotal = ptr->price * quantity;
                        cout << "Item: " << ptr->itemname << " (ID: " << ptr->itemid << "), Quantity: " << quantity << ", Total: $" << itemTotal << endl;
                        totalBill += itemTotal;
                        ptr->quantity -= quantity;
                    }
                    else
                    {
                        cout << "Not enough quantity in stock for " << ptr->itemname << " (ID: " << ptr->itemid << ")" << endl;
                    }
                    break;
                }
                ptr = ptr->next;
            }
        }

        cout << "Do you want to buy more items? (y/n): ";
        cin >> buyMore;
    } while (buyMore == 'y' || buyMore == 'Y');
}

void printBill(string customerName, string customerMobileNumber, int totalBill)
{
    cout << "==================================== SALE/INVOICE ====================================================" << endl;
    cout<<"GSTINNO-09AEEPG9990B1ZC"<<endl;
    cout<<"MOBILENO-9850309523"<<endl;
    cout<<""<<endl;
    cout<<"CUSTOMER IFORMATION=>"<<endl;
    cout << "Customer Name: " << customerName << endl;
    cout << "Mobile Number: " << customerMobileNumber << endl;
    cout << "Total Bill (including 2.5% GST): $" << totalBill * 1.025 << endl;
}

int calculateTotalCost(struct node *head)
{

    int totalCost = 0;
    struct node *ptr = head;
    while (ptr != nullptr)
    {
        totalCost += (ptr->price * (ptr->quantity - 50)); // Assuming cost per item is 50 less than the price
        ptr = ptr->next;
    }
    return totalCost;
}

int main()
{
    int wanna;
    ProductNode productHead = nullptr;
    UserNode userHead = nullptr;
    BucketItemNode bucketHead = nullptr;
    InvoiceRecordNode invoiceRecords = nullptr;
    string date;
    int choice, n, ch, original_price, nTries = 0;
    int verification;
    int newQuantity;
    int profit = 0;
    int totalBill = 0;
    int totalRevenue;
    int totalCost;
    string name;
    string productId;
    string customerName;
    string customerMobileNumber;
    AdminNode adminHead = nullptr;
    struct node1 *head = nullptr;
    struct node *head24 = nullptr;

    productHead = insertProduct(productHead, "P-1", "T-shirt", 500, 20, 250);
    productHead = insertProduct(productHead, "P-2", "Shirt", 600, 21, 300);
    productHead = insertProduct(productHead, "P-3", "Pants", 5000, 22, 2000);

    head = insertion_at_end(head, 1, "BREAD", 500, 50);
    head = insertion_at_end(head, 2, "BUTTER", 500, 50);
    head = insertion_at_end(head, 3, "JAM", 200, 40);

    head24 = insertionatend(head24, 1, "paperbags", 200, 40);
    head24 = insertionatend(head24, 2, "wallprints", 1000, 40);
    head24 = insertionatend(head24, 3, "cushions", 400, 40);
    head24 = insertionatend(head24, 4, "vases", 200, 40);
    head24 = insertionatend(head24, 5, "rugs", 450, 40);

    cout<<"------------------------Hey!! WELCOME TO S²K-----------------------------"<<endl;
    verification = login(adminHead);
    while (n != 3)
    {
        switch (verification)
        {
            case 1:
                cout<< "Welcome To The Shreshth's Cloth"<<endl;
                do
                {
                    cout << "------------------ Menu ------------" << endl;
                    cout << "1. Insert Product" << endl;
                    cout << "2. Change in Product Quantity" << endl;
                    cout << "3. Change in Product Price" << endl;
                    cout << "4. Delete Product" << endl;
                    cout << "5. Display Products" << endl;
                    cout << "6. Invoice Generation" << endl;
                    cout << "7. Profit Calculator" << endl;
                    cout << "8. Exit" << endl;

                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice)
                    {
                    case 1:
                        cout << "Enter Number of Products: ";
                        cin >> n;
                        for (int i = 1; i <= n; i++) {
                            productHead = userInsertProduct(productHead);
                        }
                        break;
                    
                    case 2:
                        cout << "Enter Number of Products: ";
                        cin >> n;
                        for (int i = 1; i <= n; i++) {
                            productHead = changeProductQuantity(productHead);
                        }
                        break;
                    
                    case 3:
                        cout << "Enter Number of Products: ";
                        cin >> n;
                        for (int i = 1; i <= n; i++) {
                            productHead = changeProductPrice(productHead);
                        }
                        break;

                    case 4:
                        cout << "Enter Number of Products: ";
                        cin >> n;
                        for (int i = 1; i <= n; i++) {
                            productHead = deleteProduct(productHead);
                        }
                        break;

                    case 5:
                        displayProducts(productHead);
                        break;

                    case 6:
                        userHead = insertUserInfo(userHead);
                        do {
                            cout << endl << "Enter the choice" << endl;
                            cout << "1. Insert Product By Product ID" << endl;
                            cout << "2. Insert Product By Name" << endl;
                            cout << "3. Exit" << endl;
                            cin >> ch;
                            switch (ch) {
                                case 1:
                                    int total;
                                    cout << "Enter Number of Products: ";
                                    cin >> n;
                                    for (int i = 1; i <= n; i++) {
                                        productId = checkProductId(productHead);
                                        cout << "Enter the quantity you want: ";
                                        cin >> newQuantity;
                                        productHead = updateProductQuantityById(productHead, newQuantity, productId);
                                        bucketHead = insertBucketItemById(productHead, bucketHead, productId, newQuantity);
                                    }
                                    date = displayUserInfo(userHead);
                                    displayBucketItems(bucketHead);
                                    total = calculateTotalPrice(bucketHead);
                                    totalsumdisplay(total);
                                    original_price = sumofogprice (bucketHead);
                                    invoiceRecords = createInvoiceRecord(invoiceRecords, total, original_price, date);
                                    bucketHead = Emptybucket (bucketHead);
                                    break;
                                case 2:
                                    cout << "Enter Number of Products: ";
                                    cin >> n;
                                    for (int i = 1; i <= n; i++) {
                                        string productName = checkProductName(productHead);
                                        cout << "Enter the quantity you want: ";
                                        cin >> newQuantity;
                                        productHead = updateProductQuantityByName(productHead, newQuantity, productName);
                                        bucketHead = insertBucketItemByName(productHead, productName, newQuantity);
                                    }
                                    date = displayUserInfo(userHead);
                                    displayBucketItems(bucketHead);
                                    total = calculateTotalPrice(bucketHead);
                                    totalsumdisplay(total);
                                    original_price = sumofogprice (bucketHead);
                                    invoiceRecords = createInvoiceRecord(invoiceRecords, total, original_price, date);
                                    bucketHead = Emptybucket (bucketHead);
                                    break;
                                case 3:
                                    break;
                                default:
                                    cout << "Entered something wrong, please try again.";
                                    break;
                            }
                        } while (ch != 3);
                        break;
                    
                    case 7:
                        calculateTotalRevenue(invoiceRecords);
                        break;
                    
                    case 8:

                        break;
                    
                    default:
                        cout << "Invalid choice. Please try again." << endl;//while close karna hai
                        break;
                    }

                } while (choice != 8);
                n=3;
                break;

            case 2:
                cout<< "Welcome To The Gupta Ji Mart"<<endl;
                do
                {
                    cout << "===== Menu =====" << endl;
                    cout << "1. Insert commodity" << endl;
                    cout << "2. Reduce commodity product_quantity" << endl;
                    cout << "3. Update commodity product_quantity" << endl;
                    cout << "4. Delete commodity" << endl;
                    cout << "5. Display Products" << endl;
                    cout << "6. Bill Creation" << endl;
                    cout << "7. Exit" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice)
                    {
                        case 1:
                            traversingstore(head);
                            int n;
                            cout << "PLEASE ENTER THE NUMBER OF ITEMS YOU WANT TO ADD IN STORE" << endl;
                            cin >> n;
                            for (int i = 0; i < n; i++)
                            {
                                head = insertionuser(head);
                            }
                            cout << "NEW PRODUCT IS BEEN ADDED IN A STORE AS SHOWN BELOW" << endl;
                            traversingstore(head);
                            break;
                        
                        case 2:
                            int numReductions;
                            cout << "Enter how many times you want to reduce product quantities: ";
                            cin >> numReductions;
                            for (int i = 0; i < numReductions; i++)
                            {
                                int pid, product_quantityToReduce;
                                cout << "Enter the commodity ID to reduce product_quantity: ";
                                cin >> pid;
                                cout << "Enter the product_quantity to reduce: ";
                                cin >> product_quantityToReduce;
                                head = reduceProductproduct_quantity(head, pid, product_quantityToReduce);
                            }
                            traversingstore(head);
                            break;
                                    
                        case 3:
                            int numUpdates;
                            cout << "Enter how many times you want to update product quantities: ";
                            cin >> numUpdates;
                            for (int i = 0; i < numUpdates; i++)
                            {
                                int pid, newproduct_quantity;
                                cout << "Enter the product ID to update product_quantity: ";
                                cin >> pid;
                                cout << "Enter the new product_quantity: ";
                                cin >> newproduct_quantity;
                                updateProductproduct_quantity(head, pid, newproduct_quantity);
                                traversingstore(head);
                            }
                            break;

                        case 4:
                            head = deletenode1(head);
                            head = updatePIDs(head);
                            break;

                        case 5:
                            traversingstore(head);
                            break;

                        case 6:
                            string customerName;
                            string customerMobile;
                            cout << "Enter customer name: ";
                            cin >> customerName;
                            cout << "Enter customer mobile number: ";
                            cin >> customerMobile;

                            int numProducts;
                            cout << "Enter how many products the customer wants to purchase: ";
                            cin >> numProducts;

                            stack<commodity *> billStack;

                            for (int i = 0; i < numProducts; i++)
                            {
                                int pid, product_quantityToReduce;
                                cout << "Enter commodity " << i + 1 << " ID: ";
                                cin >> pid;
                                cout << "Enter product_quantity for commodity " << i + 1 << ": ";
                                cin >> product_quantityToReduce;

                                // Create the bill for the customer
                                bill_creation(head, pid, customerName, customerMobile, product_quantityToReduce, billStack);
                            }

                                // Print the customer's bill
                            printBill(billStack, head, customerName, customerMobile);

                            traversingstore(head);
                            break;
                    }
                }while(choice != 7);
                n=3;
                break;
            
            case 3:
                cout<< "Welcome To The Boho Bazaar"<<endl;
                int totalCost;
                
                do
                {
                    cout<<"===================================================================================================================================="<<endl;
                    cout << "-----------------------WELCOME TO DECOR STORE-------------------------------------------------------------------------------------" << endl;
                    cout << "1. Add Products" << endl;
                    cout << "2. Reduce Product Quantity" << endl;
                    cout << "3. Update Product Quantity" << endl;
                    cout << "4. Display Inventory" << endl;
                    cout << "5.Bill Creation" << endl;
                    cout << "6. profit" << endl;
                    cout << "7. Exit" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;
                    switch (choice)
                    {
                        case 1:
                            int itemid, price, quantity;
                            int n;
                            cout << "Enter the ber of products to add: ";
                            cin >> n;
                            for (int i = 0; i < n; i++)
                            {
                                cout << "Enter item ID: ";
                                cin >> itemid;
                                cout << "Enter product name: ";
                                cin >> name;
                                cout << "Enter price: ";
                                cin >> price;
                                cout << "Enter quantity: ";
                                cin >> quantity;
                                head24 = insertion_user(head24, itemid, name, price, quantity);
                            }
                            break;

                        case 2:
                            int Reductions;
                            cout << "Enter how many times you want to reduce product quantities: ";
                            cin >> Reductions;
                            for (int i = 0; i < Reductions; i++)
                            {
                                int itemid, quantityToReduce;
                                cout << "Enter the Product ID to reduce quantity: ";
                                cin >> itemid;
                                cout << "Enter the quantity to reduce: ";
                                cin >> quantityToReduce;
                                head24 = reduceProductQuantity(head24, itemid, quantityToReduce);
                            }
                            linkedListTraversal(head24);
                            break;

                        case 3:
                            int Updates;
                            cout << "Enter how many times you want to update product quantities: ";
                            cin >> Updates;
                            for (int i = 0; i < Updates; i++)
                            {
                                int itemid, newQuantity;
                                cout << "Enter the product ID to update quantity: ";
                                cin >> itemid;
                                cout << "Enter the new quantity: ";
                                cin >> newQuantity;
                                UpdateProductQuantity(head24, itemid, newQuantity);
                                linkedListTraversal(head24);
                            }
                            break;

                        case 4:
                            linkedListTraversal(head24);
                            break;

                        case 5:
                            cout << "Enter your name: ";
                            cin >> customerName;
                            cout << "Enter your mobile number: ";
                            cin >> customerMobileNumber;
                            billCreation(head24, totalBill);
                            printBill(customerName, customerMobileNumber, totalBill);
                            break;

                        case 6:
                            totalRevenue = totalBill;
                            totalCost = calculateTotalCost(head24);
                            profit = totalRevenue - totalCost;//if there is error then change the name of profit with another variable

                            cout << "Total Revenue: $" << totalRevenue << endl;
                            cout << "Total Cost: $" << totalCost << endl;
                            cout << "Profit: $" << profit << endl;
                            break;

                        case 7:
                            cout << "Exiting the program." << endl;
                            break;
                        
                        default:
                            cout << "Invalid choice. Please enter a valid option." << endl;
                            break;
                    }
                    
                } while (choice != 7);
                n=3;
                break;

            case 0:
                do{
                cout<<"------------------------Hey!! WELCOME TO S²K-----------------------------"<<endl;
                cout<<"Enter your choice in which shop you wanna go"<<endl<<"1. Shreshth's Cloth"<<endl<<"2. Gupta Ji Mart"<<endl<<"3. Boho Bazaar"<<endl<<"4. Exit"<<endl;
                cin>>wanna;
                switch (wanna)
                {
                    case 1:
                        cout<< "Welcome To The Shreshth's Cloth";
                            do {
                                cout << "------------------ Menu ------------" << endl;
                                cout << "1. Insert Product" << endl;
                                cout << "2. Change in Product Quantity" << endl;
                                cout << "3. Change in Product Price" << endl;
                                cout << "4. Delete Product" << endl;
                                cout << "5. Display Products" << endl;
                                cout << "6. Invoice Generation" << endl;
                                cout << "7. Profit Calculator" << endl;
                                cout << "8. Exit" << endl;

                                cout << "Enter your choice: ";
                                cin >> choice;

                                switch (choice) {
                                    case 1:
                                        cout << "Enter Number of Products: ";
                                        cin >> n;
                                        for (int i = 1; i <= n; i++) {
                                            productHead = userInsertProduct(productHead);
                                        }
                                        break;
                                    case 2:
                                        cout << "Enter Number of Products: ";
                                        cin >> n;
                                        for (int i = 1; i <= n; i++) {
                                            productHead = changeProductQuantity(productHead);
                                        }
                                        break;
                                    case 3:
                                        cout << "Enter Number of Products: ";
                                        cin >> n;
                                        for (int i = 1; i <= n; i++) {
                                            productHead = changeProductPrice(productHead);
                                        }
                                        break;
                                    case 4:
                                        cout << "Enter Number of Products: ";
                                        cin >> n;
                                        for (int i = 1; i <= n; i++) {
                                            productHead = deleteProduct(productHead);
                                        }
                                        break;
                                    case 5:
                                        displayProducts(productHead);
                                        break;
                                    case 6:
                                        userHead = insertUserInfo(userHead);
                                        do {
                                            cout << endl << "Enter the choice" << endl;
                                            cout << "1. Insert Product By Product ID" << endl;
                                            cout << "2. Insert Product By Name" << endl;
                                            cout << "3. Exit" << endl;
                                            cin >> ch;
                                            switch (ch) {
                                                case 1:
                                                    int total;
                                                    cout << "Enter Number of Products: ";
                                                    cin >> n;
                                                    for (int i = 1; i <= n; i++) {
                                                        productId = checkProductId(productHead);
                                                        cout << "Enter the quantity you want: ";
                                                        cin >> newQuantity;
                                                        productHead = updateProductQuantityById(productHead, newQuantity, productId);
                                                        bucketHead = insertBucketItemById(productHead, bucketHead, productId, newQuantity);
                                                    }
                                                    date = displayUserInfo(userHead);
                                                    displayBucketItems(bucketHead);
                                                    total = calculateTotalPrice(bucketHead);
                                                    totalsumdisplay(total);
                                                    original_price = sumofogprice (bucketHead);
                                                    invoiceRecords = createInvoiceRecord(invoiceRecords, total, original_price, date);
                                                    bucketHead = Emptybucket (bucketHead);
                                                    break;
                                                case 2:
                                                    cout << "Enter Number of Products: ";
                                                    cin >> n;
                                                    for (int i = 1; i <= n; i++) {
                                                        string productName = checkProductName(productHead);
                                                        cout << "Enter the quantity you want: ";
                                                        cin >> newQuantity;
                                                        productHead = updateProductQuantityByName(productHead, newQuantity, productName);
                                                        bucketHead = insertBucketItemByName(productHead, productName, newQuantity);
                                                    }
                                                    date = displayUserInfo(userHead);
                                                    displayBucketItems(bucketHead);
                                                    total = calculateTotalPrice(bucketHead);
                                                    totalsumdisplay(total);
                                                    original_price = sumofogprice (bucketHead);
                                                    invoiceRecords = createInvoiceRecord(invoiceRecords, total, original_price, date);
                                                    bucketHead = Emptybucket (bucketHead);
                                                    break;
                                                case 3:
                                                    break;
                    
                                                default:
                                                    cout << "Entered something wrong, please try again.";
                                                    break;
                                                }
                                            } while (ch != 3);
                                            break;
                                        case 7:
                                            calculateTotalRevenue(invoiceRecords);
                                            break;
                                        case 8:
                                            break;
                                        default:
                                            cout << "Invalid choice. Please try again." << endl;
                                            break;
                                    }
                                } while (choice != 8);
                                
                        break;
                    case 2:
                                cout<< "Welcome To The Gupta Ji Mart";
                                do
                                {
                                    cout << "===== Menu =====" << endl;
                                    cout << "1. Insert commodity" << endl;
                                    cout << "2. Reduce commodity product_quantity" << endl;
                                    cout << "3. Update commodity product_quantity" << endl;
                                    cout << "4. Delete commodity" << endl;
                                    cout << "5. Display Products" << endl;
                                    cout << "6. Bill Creation" << endl;
                                    cout << "7. Exit" << endl;
                                    cout << "Enter your choice: ";
                                    cin >> choice;

                                    switch (choice)
                                    {
                                    case 1:
                                        traversingstore(head);
                                        int n;
                                        cout << "PLEASE ENTER THE NUMBER OF ITEMS YOU WANT TO ADD IN STORE" << endl;
                                        cin >> n;
                                        for (int i = 0; i < n; i++)
                                        {
                                            head = insertionuser(head);
                                        }
                                        cout << "NEW PRODUCT IS BEEN ADDED IN A STORE AS SHOWN BELOW" << endl;
                                        traversingstore(head);
                                        break;
                                    case 2:
                                        int numReductions;
                                        cout << "Enter how many times you want to reduce product quantities: ";
                                        cin >> numReductions;
                                        for (int i = 0; i < numReductions; i++)
                                        {
                                            int pid, product_quantityToReduce;
                                            cout << "Enter the commodity ID to reduce product_quantity: ";
                                            cin >> pid;
                                            cout << "Enter the product_quantity to reduce: ";
                                            cin >> product_quantityToReduce;
                                            head = reduceProductproduct_quantity(head, pid, product_quantityToReduce);
                                        }
                                        traversingstore(head);
                                        break;
                                    case 3:
                                        int numUpdates;
                                        cout << "Enter how many times you want to update product quantities: ";
                                        cin >> numUpdates;
                                        for (int i = 0; i < numUpdates; i++)
                                        {
                                            int pid, newproduct_quantity;
                                            cout << "Enter the product ID to update product_quantity: ";
                                            cin >> pid;
                                            cout << "Enter the new product_quantity: ";
                                            cin >> newproduct_quantity;
                                            updateProductproduct_quantity(head, pid, newproduct_quantity);
                                            traversingstore(head);
                                        }
                                        break;
                                    case 4:
                                        head = deletenode1(head);
                                        head = updatePIDs(head);
                                        break;
                                    case 5:
                                        traversingstore(head);
                                        break;
                                    case 6:
                                        string customerName;
                                        string customerMobile;
                                        cout << "Enter customer name: ";
                                        cin >> customerName;
                                        cout << "Enter customer mobile number: ";
                                        cin >> customerMobile;

                                        int numProducts;
                                        cout << "Enter how many products the customer wants to purchase: ";
                                        cin >> numProducts;

                                        stack<commodity *> billStack;

                                        for (int i = 0; i < numProducts; i++)
                                        {
                                            int pid, product_quantityToReduce;
                                            cout << "Enter commodity " << i + 1 << " ID: ";
                                            cin >> pid;
                                            cout << "Enter product_quantity for commodity " << i + 1 << ": ";
                                            cin >> product_quantityToReduce;

                                            // Create the bill for the customer
                                            bill_creation(head, pid, customerName, customerMobile, product_quantityToReduce, billStack);
                                        }

                                        // Print the customer's bill
                                        printBill(billStack, head, customerName, customerMobile);

                                        traversingstore(head);
                                        break;
                                    }
                                } while (choice != 7);

                        // Clean up memory by deleting all node1s
                        while (head != nullptr)
                        {
                            struct node1 *temp = head;
                            head = head->next;
                            delete temp;
                        }
                        break;
                    case 3:
                        int totalCost;
                        cout<< "Welcome To The Boho Bazaar";
                                do
                                {
                                    cout<<"===================================================================================================================================="<<endl;
                                    cout << "-----------------------WELCOME TO DECOR STORE-------------------------------------------------------------------------------------" << endl;
                                    cout << "1. Add Products" << endl;
                                    cout << "2. Reduce Product Quantity" << endl;
                                    cout << "3. Update Product Quantity" << endl;
                                    cout << "4. Display Inventory" << endl;
                                    cout << "5.Bill Creation" << endl;
                                    cout << "6. profit" << endl;
                                    cout << "7. Exit" << endl;
                                    cout << "Enter your choice: ";
                                    cin >> choice;

                                    switch (choice)
                                    {
                                    case 1: // Add Products
                                    {
                                        int itemid, price, quantity;
                                        int n;
                                        
                                        cout << "Enter the ber of products to add: ";
                                        cin >> n;
                                        for (int i = 0; i < n; i++)
                                        {
                                            cout << "Enter item ID: ";
                                            cin >> itemid;
                                            cout << "Enter product name: ";
                                            cin >> name;
                                            cout << "Enter price: ";
                                            cin >> price;
                                            cout << "Enter quantity: ";
                                            cin >> quantity;
                                            head24 = insertion_user(head24, itemid, name, price, quantity);
                                        }
                                        break;
                                    }

                                    case 2: // Reduce Product Quantity
                                    {
                                        int Reductions;
                                        cout << "Enter how many times you want to reduce product quantities: ";
                                        cin >> Reductions;
                                        for (int i = 0; i < Reductions; i++)
                                        {
                                            int itemid, quantityToReduce;
                                            cout << "Enter the Product ID to reduce quantity: ";
                                            cin >> itemid;
                                            cout << "Enter the quantity to reduce: ";
                                            cin >> quantityToReduce;
                                            head24 = reduceProductQuantity(head24, itemid, quantityToReduce);
                                        }
                                        linkedListTraversal(head24);
                                        break;
                                    }

                                    case 3: // Update Product Quantity
                                    {
                                        int Updates;
                                        cout << "Enter how many times you want to update product quantities: ";
                                        cin >> Updates;
                                        for (int i = 0; i < Updates; i++)
                                        {
                                            int itemid, newQuantity;
                                            cout << "Enter the product ID to update quantity: ";
                                            cin >> itemid;
                                            cout << "Enter the new quantity: ";
                                            cin >> newQuantity;
                                            UpdateProductQuantity(head24, itemid, newQuantity);
                                            linkedListTraversal(head24);
                                        }
                                        break;
                                    }

                                    case 4: // Display Inventory
                                        linkedListTraversal(head24);
                                        break;

                                    case 5: // Create Bill
                                    {
                                        cout << "Enter your name: ";
                                        cin >> customerName;
                                        cout << "Enter your mobile number: ";
                                        cin >> customerMobileNumber;
                                        billCreation(head24, totalBill);
                                        printBill(customerName, customerMobileNumber, totalBill);
                                        break;
                                    }

                                    case 6: // Calculate Profit
                                    {
                                        totalRevenue = totalBill;
                                        totalCost = calculateTotalCost(head24);

                                        
                                        profit = totalRevenue - totalCost;

                                        cout << "Total Revenue: $" << totalRevenue << endl;
                                        cout << "Total Cost: $" << totalCost << endl;
                                        cout << "Profit: $" << profit << endl;
                                        break;
                                    }
                                    case 7: // Exit
                                        cout << "Exiting the program." << endl;
                                        break;

                                    default:
                                        cout << "Invalid choice. Please enter a valid option." << endl;
                                        break;
                                    }
                                } while (choice != 7);
                        break;
                    case 4:
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }
                } while (wanna != 4);
                n=3;
                break;
            default:
                cout<<"You have entered wrong info";
                n++;
                break;
        }
    }
    return 0;
}

