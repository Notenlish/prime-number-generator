const std = @import("std");
const ArrayList = std.ArrayList;

pub fn main() !void {
    std.debug.print("Hello, {s}!\n", .{"World"});

    //

    const upto: u32 = 100;
    const start = 1;

    const allocator = std.heap.page_allocator;

    var list: ArrayList(u32) = .empty;
    defer list.deinit(allocator); // deinit now requires the allocator

    try list.append(allocator, 3);

    const result = basic_prime_algo(allocator, &list, start, upto);

    std.debug.print("Primes up to {}: {}\n", .{ upto, result });
}

fn basic_prime_algo(allocator: std.mem.Allocator, primes: *ArrayList(u32), start: u32, upto: u32) !void {
    const val_prime: bool = is_prime(start);
    if (val_prime) {
        try primes.append(allocator, start);
    }

    if (start == upto) {
        return;
    }
    basic_prime_algo(allocator, primes, start + 1, upto);
}

fn is_prime(value: u32) bool {
    var i: u32 = 2;
    while (i < value) {
        // std.debug.print("i:{}  value:{}\n",.{i, value});
        // divisible by i
        if ((value % i) == 0) {
            return false;
        }
        i += 1;
    }
    return true;
}
