#![no_std]
#![no_main]
#![feature(format_args_nl)]
#![feature(strict_provenance)]
#![feature(exposed_provenance)]

mod debugcon;
mod limine;

#[no_mangle]
pub extern "C" fn _start() -> ! {
    println!("Hello, world!");

    assert!(limine::BASE_REVISION.is_supported());

    loop {
        core::hint::spin_loop();
    }
}

use core::panic::PanicInfo;

#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    println!("{}", info);

    loop {
        core::hint::spin_loop();
    }
}
