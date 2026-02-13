    #include <iostream>
    #include <vector>

    int nextPow2(int n)
    {
        int k = 1;
        while(k < n) k <<= 1;

        return k;
    }

    int lowbit(int i)
    {
        return i & -i;
    }


    struct FDA
    {
        std::vector<int> bit;
        int size, ogsize;

        // 0 indexed
        void updateBit(int index, int value)
        {
            index++;
            while(index <= FDA::size)
            {
                bit[index] += value;
                index += lowbit(index);
            }
        }

        FDA()
        {

        }

        FDA(int n)
        {
            FDA::ogsize = n;
            FDA::size = nextPow2(n);

            bit.resize(FDA::size + 1, 0);
        }

        FDA(std::vector<int>& arr)
        {
            FDA::ogsize = arr.size();
            FDA::size = nextPow2(arr.size());

            bit.resize(FDA::size + 1, 0);
            
            int curr = arr[0];
            
            for(int i = 1; i <= FDA::size; i++)
            {
                bit[i] += curr;
                if(i + lowbit(i) <= FDA::size)
                    bit[i + lowbit(i)] += bit[i];

                if(i < arr.size())
                {
                    curr = arr[i] - arr[i - 1];
                }
                else curr = 0;
            }
        }

        void reconstruct(std::vector<int> arr)
        {
            FDA::ogsize = arr.size();
            FDA::size = nextPow2(arr.size());

            bit.resize(FDA::size + 1, 0);
            
            int curr = arr[0];
            
            for(int i = 1; i <= FDA::size; i++)
            {
                bit[i] += curr;
                if(i + lowbit(i) <= FDA::size)
                    bit[i + lowbit(i)] += bit[i];

                if(i < arr.size())
                {
                    curr = arr[i] - arr[i - 1];
                }
                else curr = 0;
            }
        }

        void reconstruct(int n)
        {
            FDA::ogsize = n;
            FDA::size = nextPow2(n);

            bit.resize(FDA::size + 1, 0);
        
        }

        //0 indexed
        int point_query(int index)
        {
            index++;
            int sum = 0;

            while(index)
            {
                sum += bit[index];
                index -= lowbit(index);
            }

            return sum;
        }

        //0 indexed
        void point_update(int index, int value)
        {
            int diff = value - point_query(index);
            
            updateBit(index, diff);
            updateBit(++index, -diff);
        }
        //0 indexed, inclusive
        void range_update(int l, int r, int value)
        {
            updateBit(l, value);
            if(r + 1 < FDA::size)
            {
                updateBit(r + 1, -value);
            }
        }

    };

    struct DoubleFDA
    {
        private:

        FDA Arr, X;
        int size;
        

        //0 indexed
        int getPrefixK(int k)
        {
            return (k + 1) * Arr.point_query(k) - X.point_query(k);
        }

        public:
        
        DoubleFDA(std::vector<int> arr)
        {
            DoubleFDA::Arr.reconstruct(arr);

            std::vector<int> xBase(arr.size());

            int curr = 0;
            for(int i = 0; i < xBase.size(); i++)
            {
                curr += arr[i];

                xBase[i] = (i + 1 ) * arr[i] - curr;
            }
            
            DoubleFDA::X.reconstruct(xBase);
            DoubleFDA::size = Arr.size;

        }

        //0 indexed
        void range_update(int l, int r, int increment)
        {
            Arr.range_update(l, r, increment);

            X.updateBit(l, increment * l);
            if(r + 1 <= X.size)
                X.updateBit(r + 1, -increment * (r + 1));
        }


        int range_query(int l, int r)
        {
            return getPrefixK(r) - getPrefixK(l - 1);
        }

        void point_update(int index, int increment)
        {
            range_update(index, index, increment);
        }

        int point_query(int index)
        {
            return Arr.point_query(index);
        }
    };


    int main()
    {
        int n; std::cin >> n;
        
        std::vector<int> arr(n);

        for(int i = 0; i < n; i++)
        {
            std::cin >> arr[i];
        }

        DoubleFDA fda(arr);

        for(int i = 0; i < n; i++)
        {
            std::cout << fda.point_query(i) << " ";
        }
        std::cout << std::endl;

        fda.point_update(2, 100);
        fda.point_update(3, 150);
        fda.point_update(5, 200);
        fda.point_update(7, 250);

        fda.range_update(3, 6, 5000);
        

        for(int i = 0; i < n; i++)
        {
            std::cout << fda.point_query(i) << " ";
        }
        std::cout << std::endl;

        std::cout << fda.range_query(0, 3) << std::endl;
        std::cout << fda.range_query(2, 4) << std::endl;    
        std::cout << fda.range_query(0, 8) << std::endl;

        return 0;
    }