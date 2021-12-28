class Solution {
public:
    bool validUtf8(vector<int>& data) {
        int d_ptr=0;
        const int dsize = data.size();
        while (d_ptr < data.size()) {
            uint8_t byte = (data[d_ptr] & 0xFF);  
            
            if ((byte & 0x80) == 0) {  // 1-byte
                d_ptr++;
            } else if (((byte & 0xE0) >> 5) == 6) {  // potential 2-byte
                if (d_ptr >= dsize-1) return false;   // missing next byte                
                uint8_t byte2 = (data[d_ptr+1] & 0xFF);
                if (((byte2 & 0xC0) >> 6) != 2) return false;  // invalid next byte
                d_ptr += 2;
            } else if (((byte & 0xF0) >> 4) == 14) {  // potential 3-byte
                if (d_ptr >= dsize-2) return false;   // missing last byte 
                uint8_t byte2 = (data[d_ptr+1] & 0xFF);
                uint8_t byte3 = (data[d_ptr+2] & 0xFF);
                if (((byte2 & 0xC0) >> 6) != 2) return false;  // invalid next byte
                if (((byte3 & 0xC0) >> 6) != 2) return false;  // invalid next byte
                d_ptr += 3;
            } else if (((byte & 0xF8) >> 3) == 30) {  // potential 4-byte
                if (d_ptr >= dsize-3) return false;   // missing last byte 
                uint8_t byte2 = (data[d_ptr+1] & 0xFF);
                uint8_t byte3 = (data[d_ptr+2] & 0xFF);
                uint8_t byte4 = (data[d_ptr+3] & 0xFF);                
                if (((byte2 & 0xC0) >> 6) != 2) return false;  // invalid next byte
                if (((byte3 & 0xC0) >> 6) != 2) return false;  // invalid next byte
                if (((byte4 & 0xC0) >> 6) != 2) return false;  // invalid next byte
                d_ptr += 4;
            } else {  // unknown...
                return false;
            }
        }
        return true;  // consumed everything, decoded everything properly
    }
};
