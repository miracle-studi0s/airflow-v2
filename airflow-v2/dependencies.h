#pragma once

#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <algorithm>
#include <filesystem>
#include <d3d11.h>
#include <dxgi.h>
#include <xmmintrin.h>
#include <Windows.h>

#include "dependencies/lazy_importer.hpp"
#include "dependencies/fnv1a.hpp"
#include "dependencies/hash.hpp"
#include "dependencies/syscall.hpp"
#include "dependencies/xor.hpp"