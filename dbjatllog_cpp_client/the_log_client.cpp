
#import "../dbjatllog_server/bteclog.tlb" rename_namespace("dbjlog")


void log(const char* txt_)
{
	dbjlog::IthelogPtr loggy(L"{CE863F40799C11D294EF000000000000}") ;

	assert( loggy );

	loggy->Putlogfilename(_bstr_t(L"logfile.log"));

	_bstr_t log_file_path = loggy->Getlogfilename();

}