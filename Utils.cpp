namespace Skele_lib {
	namespace Utils {

		bool GetKeyDown(int key) {//returns if the key 'key' is pressed 
			return GetAsyncKeyState(key) >> 15;
		}

	}
}