/*

1005. Maximize Sum Of Array After K Negations

Given an array A of integers, we must modify the array in the following way: we choose an i and replace 
A[i] with -A[i], and we repeat this process K times in total.  (We may choose the same index i multiple 
times.)

Return the largest possible sum of the array after modifying it in this way.

Example 1:

Input: A = [4,2,3], K = 1
Output: 5
Explanation: Choose indices (1,) and A becomes [4,-2,3].
Example 2:

Input: A = [3,-1,0,2], K = 3
Output: 6
Explanation: Choose indices (1, 2, 2) and A becomes [3,1,0,2].
Example 3:

Input: A = [2,-3,-1,5,-4], K = 2
Output: 13
Explanation: Choose indices (1, 4) and A becomes [2,3,-1,5,4].
 
Note:

1 <= A.length <= 10000
1 <= K <= 10000
-100 <= A[i] <= 100

*/

class Solution {
public:
    int largestSumAfterKNegations(vector<int>& A, int K) {
        // Build a min heap
        make_heap(A.begin(), A.end(), greater<int>());
        
        // Toggle min element K time
        // If the min element is -ive it will increase sum else
        // if it +ive it will decrease sum by min amount 
        for (int i = 0; i < K; ++i) {
            // Move min/top to back and reheapify rest
            pop_heap(A.begin(), A.end(), greater<int>()); 
            
            // Pop min
            int v = A.back();
            A.pop_back();
            
            // Toggle it and push back
            A.push_back(-1 * v);      
            
            // Reheapify - last with rest
            push_heap(A.begin(), A.end(), greater<int>());
        }
        
        // Return max sum
        return accumulate(A.begin(), A.end(), 0);   
    }
};

class Solution {
public:
    int largestSumAfterKNegations(vector<int>& A, int K) {
        int N = A.size();
        int sum = 0;
        priority_queue<int> maxPq;
        
        // 1. Find K min items and put them in PQ. Sum items except K min items.
        for (int i = 0; i < N; ++i) {
            if (i < K) {
                // Push first K items in PQ
                maxPq.push(A[i]);
            } else {
                // Replace PQ top with curr if it is greater
                if (maxPq.top() > A[i]) {
                    sum += maxPq.top();
                    maxPq.pop();
                    maxPq.push(A[i]);
                } else {
                    sum += A[i];
                }
            }
        }

        // Build min pr
        priority_queue<int, vector<int>, greater<int>> minPq;
        
        while (!maxPq.empty()) {
            minPq.push(maxPq.top());
            maxPq.pop();
        }
        
        int absMinItem = INT_MAX/2;
        
        while (!minPq.empty()) {
            int top = minPq.top();
            
            if (K) {
                if (top < 0) {
                    // Make negative items postive and add
                    sum -= top;
                    --K;
                    absMinItem = abs(top);
                } else {
                    // Toggle current item or an already processed negative number 
                    if (K % 2) {
                        if (absMinItem < top) {
                            // Already prossed item has smaller absolute value
                            // Subtract it twice as it was already added
                            sum -= 2 * absMinItem;
                            
                            // Add current item
                            sum += top;
                        } else {
                            // Subtract current item
                            sum -= top;
                        }
                    } else {
                        // Toggle even of times any already processed number
                        sum += top;
                    }
                    
                    K = 0;
                }
            } else {  
                // Add all other items
                sum += top;
            }
            
            minPq.pop();
        }
        
        return sum;
    }
};
