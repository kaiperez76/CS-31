//
//  main.cpp
//  Project 3
//
//  Created by Kai Perez on 10/17/22.
//

#include <iostream>
#include <cctype>
#include <cassert>
#include <string>
using namespace std;



bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
        "LA.ME.MA.MD.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
        "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY"
    
        "Al.Ak.Az.Ar.Ca.Co.Ct.De.Fl.Ga.Hi.Id.Il.In.Ia.Ks.Ky."
        "La.Me.Ma.Md.Mi.Mn.Ms.Mo.Mt.Ne.Nv.Nh.Nj.Nm.Ny.Nc.Nd."
        "Oh.Ok.Or.Pa.Ri.Sc.Sd.Tn.Tx.Ut.Vt.Va.Wa.Wv.Wi.Wy"
    
        "aL.aK.aZ.aR.cA.cO.cT.dE.fL.gA.hI.iD.iL.iN.iA.kS.kY."
        "lA.mE.mA.mD.mI.mN.mS.mO.mT.nE.nV.nH.nJ.nM.nY.nC.nD."
        "oH.oK.oR.pA.rI.sC.sD.tN.tX.uT.vT.vA.wA.wV.wI.wY"
    
        "al.ak.az.ar.ca.co.ct.de.fl.ga.hi.id.il.in.ia.ks.ky."
        "la.me.ma.md.mi.mn.ms.mo.mt.ne.nv.nh.nj.nm.ny.nc.nd."
        "oh.ok.or.pa.ri.sc.sd.tn.tx.ut.vt.va.wa.wv.wi.wy";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}


bool stateAfterComma (string pollData, int pos)     //Validity of states after commas
{
    pos = pos + 2;
    return isValidUppercaseStateCode(pollData.substr(pos - 1, 2));
}





bool isValidPollString(string pollData)
{
    if (!isValidUppercaseStateCode((pollData.substr(0,2))))     //Checking state code
        return false;
    int manyNum = 0;
    for (int k = 2; k < pollData.size() ; k++)
    {
        if (isdigit(pollData.at(k))){        //ensuring maximum of 2 nums in a row
            manyNum++;
            if (manyNum > 2)
                return false;}
        if (isalpha(pollData.at(k)) && (pollData.at(k - 1) != ',') &&
            (pollData.at(k - 2) != ',') ){  //if a letter appears it resets num count to 0
            manyNum = 0;
            if((isalpha(pollData.at(k)) && isalpha(pollData.at(k - 1)))){
                return false;
                }
        }
        if(pollData.at(k) == ',')                 //Validity of states after commas
            if (!stateAfterComma (pollData, k)){
                return false;
            }
        if(!(isalpha(pollData.at(k))) && !(isdigit(pollData.at(k))) &&
           pollData.at(k) != ',')              // only nums chars and commas
            return false;
        if (isdigit(pollData.at(pollData.size()-1)))
            return false;
    }
return true;
}




int addingVotes (string pollData, int pos)     //adding 2 chars that represent nums
{
    return ((pollData.at(pos)-48) * 10) + (pollData.at(pos+1) - 48);
}






int countSeats(string pollData, char party, int& seatCount)
{

    int tempCount = 0;
    //invalid party input and pollData
    if ((!isalpha(party)) && !isValidPollString(pollData)){
        return 1;}
    if (!isalpha(party)){               //invalid party input
        return 2;}
    if (!isValidPollString(pollData)){  //invalid pollData
        return 1;}
    if (isValidPollString(pollData) && (isalpha(party))){   //Valid pollData and party
        seatCount = 0;
        for (int k = 0; k < pollData.size();k++)
        {
            if (isdigit(pollData.at(k)))        // is it a number
            {
                if(isdigit(pollData.at(k+1))){       //calc if the following char is a num
                    tempCount += addingVotes(pollData, k);
                }
                if(!isdigit(pollData.at(k+1)) && !isdigit(pollData.at(k-1)))
                {                        //calc if neither following nor preceding is num
                    tempCount += (pollData.at(k)-48);
                }
            }
            if (isalpha(pollData.at(k)))            //is a letter
            {
                if(pollData.at(k) == party || pollData.at(k) == toupper(party) || pollData.at(k) == tolower(party) )    //if it is party intended
                {
                    seatCount += tempCount;
                    tempCount = 0;
                }
                if (pollData.at(k) != party || pollData.at(k) != toupper(party) || pollData.at(k) != tolower(party)) //if not partyintended cancel counting
                    tempCount = 0;
            }
        }
       
    }
return 0;
}


int main()
{
    int seatCount = -77;
    //cerr << isValidPollString("ct5d,ny9r17d1i") << endl;
    //cerr <<countSeats("Ny15d,vT,Ct15f98d", 'd', seatCount) << endl;
    cerr << seatCount << endl;
    cerr << countSeats("ct5d,ny9r17d1i", '$', seatCount) << endl;
    cerr << seatCount << endl;
}
