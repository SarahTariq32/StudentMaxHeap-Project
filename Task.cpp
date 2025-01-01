#include<iostream>
using namespace std;
class Student
{
    friend class StudentMaxHeap;
    private:
        int rollNo; /** Student’s roll number */
        double cgpa; /** Student’s CGPA */
    public:
        Student(int rollNo=0,double cgpa=0.0){
            this->rollNo=rollNo;
            this->cgpa=cgpa;
        }
};

class StudentMaxHeap
{
    private:

        Student* arr; /** Array of students arranged like a Max Heap */
        int curSize; /** Current number of students present in the heap */
        int maxSize; /** Maximum number of students that can be present in the heap */

        void heapify(int index){
            int largest=index;
            int left= 2*index+1;
            int right=2*index+1;

            if(left<curSize && (arr[left].cgpa>arr[largest].cgpa) || (arr[left].cgpa==arr[largest].cgpa && arr[largest].rollNo>arr[left].rollNo)){
                largest=left;
            }
            if(right<curSize && (arr[right].cgpa>arr[largest].cgpa) || (arr[right].cgpa==arr[largest].cgpa && arr[largest].rollNo>arr[right].rollNo)){
                largest=right;
            }

            if(index!=largest){
                Student temp = arr[index];
                arr[index] = arr[largest];
                arr[largest] = temp;
                heapify(largest);
            }
        }

    public:

        StudentMaxHeap(int size){
            arr=new Student[size];
            curSize=0;
            maxSize=size;        
        }

        ~StudentMaxHeap(){
            delete arr;
        }

        bool remove(int& rollNo, double& cgpa){
            rollNo=arr[0].rollNo;
            cgpa=arr[0].cgpa;

            arr[0].rollNo=arr[curSize-1].rollNo;
            arr[0].cgpa=arr[curSize-1].cgpa;

            curSize--;
            heapify(0);
            return true;          
        }

        void insert(int rollNo, double cgpa) {
            if (isFull()) cout<<"INSERTION ERROR. NO SPACE AVAILABLE.\n";

            Student newStudent(rollNo,cgpa);
            arr[curSize] = newStudent; 
            int newNode = curSize;
            curSize++;

            while (newNode != 0) {
                int parentIndex = (newNode - 1) / 2;
                if (arr[newNode].cgpa > arr[parentIndex].cgpa || (arr[newNode].cgpa == arr[parentIndex].cgpa && arr[newNode].rollNo < arr[parentIndex].rollNo)) {
                    swap(arr[newNode], arr[parentIndex]);
                    newNode = parentIndex;
                } else {
                    break;
                }
            }
        }

        void displayStudentList(){
            for(int i=0;i<curSize;i++){
                cout<<"Roll No = "<<arr[i].rollNo<<"  "<<"CGPA  = "<<arr[i].cgpa<<"\n";
            }
        }

        void levelOrder() {
            cout << "Heap: Level order traversal:" << endl;
            int level=1;
            int j=0;
            for (int i = 0; i < curSize; i++) {
                cout << "Roll No: " << arr[i].rollNo << ", CGPA: " << arr[i].cgpa << "\t";
                j++;
                if(level==j){
                    cout<<endl;
                    if(level==1) level=2;
                    else level=level*2;
                    j=0;
                }
            }
        }

        bool isEmpty(){
            if(curSize==0) return true;
            return false;
        }

        bool isFull(){
            if(maxSize==curSize) return true;
            return false;
        }
};
void menu() {
    int maxSize;
    cout << "ENTER MAX SIZE OF HEAP : ";
    cin >> maxSize;

    StudentMaxHeap heap(maxSize);
    int choice;

    do {
        cout << "\nMenu:" << endl;
        cout << "1. Insert a new student" << endl;
        cout << "2. Remove (and display) the student with the Max CGPA" << endl;
        cout << "3. Display the list of students (Descending order of CGPA)" << endl;
        cout << "4. Display the list of students (Level-order traversal)" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int rollNo;
            double cgpa;
            cout << "Enter roll number: ";
            cin >> rollNo;
            cout << "Enter CGPA: ";
            cin >> cgpa;
            heap.insert(rollNo, cgpa);

        } else if (choice == 2) {
            int rollNo;
            double cgpa;
            if (heap.remove(rollNo, cgpa)) {
                cout << "REMOVED STUDENT - Roll No: " << rollNo << ", CGPA: " << cgpa << endl;
            } else {
                cout << "Heap is empty. Cannot remove." << endl;
            }
        } else if (choice == 3) {

            cout << "Students in descending order of CGPA:" << endl;
            heap.displayStudentList();

        } else if (choice == 4) {

            heap.levelOrder();

        } else if (choice == 5) {

            cout << "Exiting..." << endl;

        } else {
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 5);
}

int main() {
    menu();
    return 0;
}




















































































































#include <iostream>
using namespace std;

class Student {
    friend class StudentMaxHeap;
private:
    double cgpa; // Student’s CGPA
    int rollNo;  // Student’s roll number
public:
    Student(double cgpa=0.0,int rollNo=0){
        this->cgpa=cgpa;
        this->rollNo=rollNo;
    }
};

class StudentMaxHeap {
private:
    Student* arr;   // Array used as a Max Heap
    int curSize;    // Current number of students
    int maxSize;    // Maximum capacity of the heap

    // void heapifyUp(int index) {
    //     while (index > 0) {
    //         int parent = (index - 1) / 2;
    //         if (arr[index].cgpa > arr[parent].cgpa || 
    //             (arr[index].cgpa == arr[parent].cgpa && arr[index].rollNo < arr[parent].rollNo)) {
    //             swap(arr[index], arr[parent]);
    //             index = parent;
    //         } else {
    //             break;
    //         }
    //     }
    // }

    // void heapifyDown(int index) {
    //     while (true) {
    //         int largest = index;
    //         int left = 2 * index + 1;
    //         int right = 2 * index + 2;

    //         if (left < curSize && (arr[left].cgpa > arr[largest].cgpa || 
    //             (arr[left].cgpa == arr[largest].cgpa && arr[left].rollNo < arr[largest].rollNo))) {
    //             largest = left;
    //         }
    //         if (right < curSize && (arr[right].cgpa > arr[largest].cgpa || 
    //             (arr[right].cgpa == arr[largest].cgpa && arr[right].rollNo < arr[largest].rollNo))) {
    //             largest = right;
    //         }
    //         if (largest != index) {
    //             swap(arr[index], arr[largest]);
    //             index = largest;
    //         } else {
    //             break;
    //         }
    //     }
    // }
    void heapify(int index) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < curSize && (arr[left].cgpa > arr[largest].cgpa || 
            (arr[left].cgpa == arr[largest].cgpa && arr[left].rollNo < arr[largest].rollNo))) {
            largest = left;
        }

        if (right < curSize && (arr[right].cgpa > arr[largest].cgpa || 
            (arr[right].cgpa == arr[largest].cgpa && arr[right].rollNo < arr[largest].rollNo))) {
            largest = right;
        }

        if (largest != index) {
            Student temp = arr[index];
            arr[index] = arr[largest];
            arr[largest] = temp;
            heapify(largest);
        }
    }


public:
    StudentMaxHeap(int size) : maxSize(size), curSize(0) {
        arr = new Student[maxSize];
    }

    ~StudentMaxHeap() {
        delete[] arr;
    }

    bool isEmpty() {
        if(curSize==0) return true;
        return false;
    }

    bool isFull() {
        if(curSize==maxSize) return true;
        return false;
    }

    // bool insert(int rollNo, double cgpa) {
    //     if (isFull()) return false;

    //     arr[curSize].rollNo = rollNo;
    //     arr[curSize].cgpa = cgpa;
    //     curSize++;

    //     heapifyUp(curSize - 1);
    //     return true;
    // }

    bool insert(int rollNo, double cgpa) {
        if (isFull()) return false;

        Student newStudent(cgpa,rollNo);
        arr[curSize] = newStudent; 
        int newNode = curSize;
        curSize++;

        while (newNode != 0) {
            int parentIndex = (newNode - 1) / 2;
            if (arr[newNode].cgpa > arr[parentIndex].cgpa || (arr[newNode].cgpa == arr[parentIndex].cgpa && arr[newNode].rollNo < arr[parentIndex].rollNo)) {
            swap(arr[newNode], arr[parentIndex]);
            newNode = parentIndex;
            } else {
                break;
            }
        }
        return true;
    }



    bool remove(int &rollNo, double &cgpa) {
        if (isEmpty()) return false;

        rollNo = arr[0].rollNo;
        cgpa = arr[0].cgpa;

        arr[0] = arr[curSize - 1];
        curSize--;

        heapify(0);
        return true;
    }

    void displayStudentList() {
        for (int i = 0; i < curSize; i++) {
            cout << "Roll No: " << arr[i].rollNo << ", CGPA: " << arr[i].cgpa << endl;
        }
    }

    void levelOrder() {
        cout << "Heap: Level order traversal:" << endl;
        int j=1;
        for (int i = 0; i < curSize; i++) {
            cout << "Roll No: " << arr[i].rollNo << ", CGPA: " << arr[i].cgpa << "\t";
            if(i-1==j){
                cout<<endl;
                if(j=1) j=2;
                else j=j*2;
            }
        }
    }
};

void menu() {
    int maxSize;
    cout << "Enter the maximum size of the heap: ";
    cin >> maxSize;

    StudentMaxHeap heap(maxSize);
    int choice;

    do {
        cout << "\nMenu:" << endl;
        cout << "1. Insert a new student" << endl;
        cout << "2. Remove (and display) the student with the Max CGPA" << endl;
        cout << "3. Display the list of students (Descending order of CGPA)" << endl;
        cout << "4. Display the list of students (Level-order traversal)" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int rollNo;
            double cgpa;
            cout << "Enter roll number: ";
            cin >> rollNo;
            cout << "Enter CGPA: ";
            cin >> cgpa;

            if (heap.insert(rollNo, cgpa)) {
                cout << "Student inserted successfully." << endl;
            } else {
                cout << "Heap is full. Cannot insert." << endl;
            }
        } else if (choice == 2) {
            int rollNo;
            double cgpa;
            if (heap.remove(rollNo, cgpa)) {
                cout << "Removed student - Roll No: " << rollNo << ", CGPA: " << cgpa << endl;
            } else {
                cout << "Heap is empty. Cannot remove." << endl;
            }
        } else if (choice == 3) {
            cout << "Students in descending order of CGPA:" << endl;
            heap.displayStudentList();
        } else if (choice == 4) {
            heap.levelOrder();
        } else if (choice == 5) {
            cout << "Exiting..." << endl;
        } else {
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 5);
}

int main() {
    menu();
    return 0;
}
