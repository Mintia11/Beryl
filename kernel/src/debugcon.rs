use core::fmt::{Arguments, Write};

pub struct DebugCon;

impl Write for DebugCon {
    #[inline]
    fn write_str(&mut self, s: &str) -> core::fmt::Result {
        unsafe {
            core::arch::asm!("rep outsb", in("rsi") s.as_ptr(), in("rcx") s.len(), in("dx") 0xE9, options(nostack, readonly));
        }

        Ok(())
    }
}

#[doc(hidden)]
pub fn _print(args: Arguments) {
    let _ = DebugCon::write_fmt(&mut DebugCon, args);
}

#[macro_export]
macro_rules! print {
    ($($arg:tt)*) => {
        $crate::debugcon::_print(format_args!($($arg)*))
    };
}

#[macro_export]
macro_rules! println {
    () => {
        $crate::print!("\n")
    };

    ($($arg:tt)*) => {
        $crate::debugcon::_print(format_args_nl!($($arg)*))
    };
}
