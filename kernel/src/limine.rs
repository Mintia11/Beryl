use limine::{
    request::{RequestsEndMarker, RequestsStartMarker},
    BaseRevision,
};

#[used]
#[link_section = ".requests_start_marker"]
static _START_MARKER: RequestsStartMarker = RequestsStartMarker::new();

#[used]
#[link_section = ".requests_end_marker"]
static _END_MARKER: RequestsEndMarker = RequestsEndMarker::new();

macro_rules! limine_request {
    ($name:ident, $typ:ty, $constr:expr) => {
        #[used]
        #[link_section = ".requests"]
        pub static $name: $typ = $constr;
    };
}

limine_request!(BASE_REVISION, BaseRevision, BaseRevision::new());
