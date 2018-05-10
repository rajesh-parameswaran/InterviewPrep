// XMLFormater.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <msxml6.h>

int _tmain(int argc, _TCHAR* argv[])
{
	CoInitialize(NULL);
	IXMLDOMDocument *pXMLDom = NULL;
	BSTR bstrXML = NULL;
	VARIANT_BOOL varStatus;
	VARIANT varFileName;

	VariantInit(&varFileName);

	bstrXML = SysAllocString(L"<r>\n<t>top</t>\n<b>bottom</b>\n</r>");

	HRESULT hr = CoCreateInstance(__uuidof(DOMDocument60), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pXMLDom));
	if (SUCCEEDED(hr))
	{
		// these methods should not fail so don't inspect result
		(pXMLDom)->put_async(VARIANT_FALSE);
		(pXMLDom)->put_validateOnParse(VARIANT_FALSE);
		(pXMLDom)->put_resolveExternals(VARIANT_FALSE);
	}

	pXMLDom->loadXML(bstrXML, &varStatus);

	if (varStatus == VARIANT_TRUE)
	{
		pXMLDom->get_xml(&bstrXML);
		printf("XML DOM loaded from app:\n%S\n", bstrXML);

		BSTR bstrString = SysAllocString(L"C:\\MyData.xml");
		V_VT(&varFileName) = VT_BSTR;
		V_BSTR(&varFileName) = bstrString;

		pXMLDom->save(varFileName);

		printf("XML DOM saved to myData.xml\n");
	}


	CoUninitialize();
	return 0;
}

