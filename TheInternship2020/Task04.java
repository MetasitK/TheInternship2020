import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;

public class Task04 {
    private static CompanyInformation[] sendedCmpInfo;
    public static void main(String[] args) throws UnsupportedEncodingException {
        List<CompanyInformation> company = new ArrayList<>();
        boolean passTheTopic = false;
        String info = getUrlInfo("https://theinternship.io/");
        char[] charInfo = new char[info.length()];
        for (int i = 0; i < info.length(); i++) {
            charInfo[i] = info.charAt(i);
        }
        for (int i = 0; i < info.length(); i++) {
            if (!passTheTopic) {
                if (addCompName(charInfo, i, "Participating Startups") != null) {
                    passTheTopic = true;
                }
            } else {
                if (addCompanyInfo(charInfo, i) != null) {
                    company.add(addCompanyInfo(charInfo, i));
                }
                if (addCompName(charInfo, i, "FAQ") != null) {
                    break;
                }
            }
        }
        sendedCmpInfo = new CompanyInformation[company.size()];
        Collections.sort(company, new SortByNumber());
        int sendCompanyIndex = 0;
        for (CompanyInformation cmpInfo : company) {
            System.out.println(cmpInfo.imageName);
            sendedCmpInfo[sendCompanyIndex++] = cmpInfo;
        }
        try {
            JavaToJSONFormat.run();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
    private static CompanyInformation addCompanyInfo(char[] c, int index){
        CompanyInformation company = new CompanyInformation();
        company.linkName = addCompName(c, index, "href=\"");
        company.nDescriptionCharacters = 0;
        if(company.linkName == null) return null;
        int i = index;
        while(true){
            if(addCompName(c, i, "img src=\"") != null){
                company.imageName =  addCompName(c, i, "img src=\"");
                break;
            }
            i++;
        }

        i = index;
        boolean count = false;
        while(true){
            if(addCompName(c, i, "span class=\"list-company\"") != null){
                if(!count){
                    count = true;
                    while(c[i] != '>'){
                        i++;
                    }
                    i++;
                }
            }
            else if(count){
                if(addCompName(c, i, "/span") != null){
                    break;
                }
                company.nDescriptionCharacters++;
            }
            i++;
        }
        return company;
    }

    private static String addCompName(char[] c, int index, String compare) {
        for (int i = index; i < compare.length() + index; i++) {
            if (c[i] != compare.charAt(i - index)) {
                return null;
            }
        }
        StringBuilder string = new StringBuilder();
        int i = compare.length() + index - 1;
        while (c[i] != '\"') {
            i--;
        }
        i++;
        do{
            string.append(c[i]);
            i++;
        }while (c[i] != '\"');
        return string.toString();
    }

    

    private static  String getUrlInfo(String url) {
        StringBuilder info = new StringBuilder();
        URL internURL;
        try {
            internURL = new URL(url);
            URLConnection connection = internURL.openConnection();
            BufferedReader inReader = new BufferedReader(new InputStreamReader(connection.getInputStream(),"UTF-8"));
            String line;
            while((line = inReader.readLine()) != null)
            {
                info.append(line + "\n");
            }
            inReader.close();
        } catch (MalformedURLException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return info.toString();
    }
    public static CompanyInformation[] getCompany(){
        return sendedCmpInfo;
    }
}

class CompanyInformation{
    public String linkName;
    public String imageName;
    public int nDescriptionCharacters;
}

class SortByNumber implements Comparator<CompanyInformation>{
    public int compare(CompanyInformation cmp1, CompanyInformation cmp2){
        return cmp1.nDescriptionCharacters - cmp2.nDescriptionCharacters;
    }
}


class JavaToJSONFormat {
    public static void run() throws IOException {
        CompanyInformation[] companyInfo = new CompanyInformation[Task04.getCompany().length];
        companyInfo = Task04.getCompany();
        FileWriter out = new FileWriter("Logo.json");
        try {
            out.write("{ \"companies\" : [\n");
            for (int i = 0 ; i < Task04.getCompany().length ; i++) {
                out.write(format(companyInfo[i].imageName));
                if(i < Task04.getCompany().length - 1){
                    out.write(",\n");
                }
            }
            out.write("\n] }");
        } catch (FileNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        out.close();
    }

    private static String format(String url) {
        return "\t{ \"logo\": \"https:theinternship.io/"+ url +"\"}";
    }
}
